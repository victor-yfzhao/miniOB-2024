/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>

#include "common/defs.h"
#include "common/lang/string.h"
#include "common/lang/span.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "storage/db/db.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/index/index.h"
#include "storage/record/record_manager.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir,
    span<const AttrInfoSqlNode> attributes, StorageFormat storage_format)
{
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attributes.size() == 0) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  const vector<FieldMeta> *trx_fields = db->trx_kit().trx_fields();
  if ((rc = table_meta_.init(table_id, name, trx_fields, attributes, storage_format)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  fstream fs;
  fs.open(path, ios_base::out | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  string             data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm       = db->buffer_pool_manager();
  rc                           = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::open(Db *db, const char *meta_file, const char *base_dir)
{
  // 加载元数据文件
  fstream fs;
  string  meta_file_path = string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, ios_base::in | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR_OPEN;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::INTERNAL;
  }
  fs.close();

  db_       = db;
  base_dir_ = base_dir;

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const FieldMeta *field_meta = table_meta_.field(index_meta->field());

    if (index_meta->children().size() > 0) {
      MultiIndex *multi_index = new MultiIndex(*index_meta);
      indexes_.push_back(multi_index);
      continue;
    }

    if (field_meta == nullptr) {
      LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                name(), index_meta->name(), index_meta->field());
      // skip cleanup
      //  do all cleanup action in destructive Table function
      return RC::INTERNAL;
    }

    BplusTreeIndex *index      = new BplusTreeIndex();
    string          index_file = table_index_file(base_dir, name(), index_meta->name());

    rc = index->open(this, index_file.c_str(), *index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%s",
                name(), index_meta->name(), index_file.c_str(), strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  return rc;
}

RC Table::insert_record(Record &record, Trx *trx)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->insert_record(record.data(), table_meta_.record_size(), &record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid(), trx);
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/, trx);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

RC Table::visit_record(const RID &rid, function<bool(Record &)> visitor)
{
  return record_handler_->visit_record(rid, visitor);
}

RC Table::get_record(const RID &rid, Record &record)
{
  RC rc = record_handler_->get_record(rid, record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to visit record. rid=%s, table=%s, rc=%s", rid.to_string().c_str(), name(), strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::recover_insert_record(Record &record)
{
  RC rc = RC::SUCCESS;
  rc    = record_handler_->recover_insert_record(record.data(), table_meta_.record_size(), record.rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%s", table_meta_.name(), strrc(rc));
    return rc;
  }

  rc = insert_entry_of_indexes(record.data(), record.rid(), nullptr);
  if (rc != RC::SUCCESS) {  // 可能出现了键值重复
    RC rc2 = delete_entry_of_indexes(record.data(), record.rid(), false /*error_on_not_exists*/, nullptr);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record.rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
  }
  return rc;
}

const char *Table::name() const { return table_meta_.name(); }

const TableMeta &Table::table_meta() const { return table_meta_; }

RC Table::make_record(int value_num, const Value *values, Record &record)
{
  RC rc = RC::SUCCESS;
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() + 1 != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  // 复制所有字段的值
  int   record_size = table_meta_.record_size();
  char *record_data = (char *)malloc(record_size);
  memset(record_data, 0, record_size);

  const FieldMeta *null_tag_field = table_meta_.field("_null_tag");
  string             null_tag_string(null_tag_field->len(), '0');

  for (int i = 0; i < value_num && OB_SUCC(rc); i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &    value = values[i];

    if (AttrType::NULLS == value.attr_type()){
      if (!field->nullable()) {
        LOG_WARN("field is not nullable. table name:%s,field name:%s", table_meta_.name(), field->name());
        rc = RC::SCHEMA_FIELD_MISSING;
        break;
      }
      null_tag_string[i] = '1';
      continue;
    }

    if (field->type() != value.attr_type()) {
      Value real_value;
      rc = Value::cast_to(value, field->type(), real_value);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to cast value. table name:%s,field name:%s,value:%s ",
            table_meta_.name(), field->name(), value.to_string().c_str());
        break;
      }
      rc = set_value_to_record(record_data, real_value, field);
    } else {
      rc = set_value_to_record(record_data, value, field);
    }
  }
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to make record. table name:%s", table_meta_.name());
    free(record_data);
    return rc;
  }

  Value null_tag_value(null_tag_string.c_str(), null_tag_string.length());
  rc = set_value_to_record(record_data, null_tag_value, null_tag_field);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to make record's null tag. table name:%s", table_meta_.name());
    free(record_data);
    return rc;
  }

  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

RC Table::set_value_to_record(char *record_data, const Value &value, const FieldMeta *field)
{
  size_t       copy_len = field->len();
  const size_t data_len = value.length();
  if (field->type() == AttrType::CHARS) {
    if (copy_len > data_len) {
      copy_len = data_len + 1;
    }
  }
  if (field->type() == AttrType::VECTORS) {
    if (copy_len != data_len) {
      return RC::INVALID_ARGUMENT;
    }
  memcpy(record_data + field->offset(), value.data(), sizeof(uintptr_t));
  return RC::SUCCESS;
  }
  memcpy(record_data + field->offset(), value.data(), copy_len);
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  string data_file = table_data_file(base_dir, table_meta_.name());

  BufferPoolManager &bpm = db_->buffer_pool_manager();
  RC                 rc  = bpm.open_file(db_->log_handler(), data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler(table_meta_.storage_format());

  rc = record_handler_->init(*data_buffer_pool_, db_->log_handler(), &table_meta_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%s", strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner, Trx *trx, ReadWriteMode mode)
{
  RC rc = scanner.open_scan(this, *data_buffer_pool_, trx, db_->log_handler(), mode, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::get_chunk_scanner(ChunkFileScanner &scanner, Trx *trx, ReadWriteMode mode)
{
  RC rc = scanner.open_scan_chunk(this, *data_buffer_pool_, db_->log_handler(), mode);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%s", strrc(rc));
  }
  return rc;
}

RC Table::create_index(Trx *trx, const FieldMeta *field_meta, const char *index_name, bool unique)
{
  if (common::is_blank(index_name) || nullptr == field_meta) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }

  IndexMeta new_index_meta;

  RC rc = new_index_meta.init(index_name, *field_meta, unique);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s, field_name:%s", 
             name(), index_name, field_meta->name());
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index      = new BplusTreeIndex();
  string          index_file = table_index_file(base_dir_.c_str(), name(), index_name);

  rc = index->create(this, index_file.c_str(), new_index_meta, *field_meta);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s", 
             name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    rc = index->insert_entry(record.data(), &record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
             name(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

  indexes_.push_back(index);

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::create_multi_index(Trx *trx, const vector<FieldMeta> &field_metas, const char *index_name, bool unique)
{
  if (common::is_blank(index_name) || field_metas.size() == 0) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }

  for(Index *index : indexes_) {
    if (strcmp(index->index_meta().name(), index_name) == 0) {
      LOG_ERROR("Index %s has been created, cannot create multi-index on it", index_name);
      return RC::SCHEMA_INDEX_NAME_REPEAT;
    }

    // if (index->index_meta().children().size() > 0) continue;

    // const char *_field = index->index_meta().field();

    // for (FieldMeta field_meta : field_metas) {
    //   if (strcmp(_field, field_meta.name()) == 0) {
    //     LOG_ERROR("Field %s has been indexed, cannot create multi-index on it", _field);
    //     return RC::SCHEMA_INDEX_NAME_REPEAT;
    //   }
    // }
  }

  // build parent index meta to describe the whole multi-index
  IndexMeta new_multi_index_meta;

  RC rc = new_multi_index_meta.init_multi(index_name, unique);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s", name(), index_name);
    return rc;
  }

  // MultiIndex *multi_index = new MultiIndex(new_multi_index_meta);
  vector<Index *> child_indexes;

  // IndexMeta multi_index_meta = multi_index->index_meta();

  // build each index in multi-index
  for (size_t i = 0; i < field_metas.size(); i++) {
    IndexMeta new_child_index_meta;
    string child_index_name = (string)index_name + "_" + std::to_string(i);

    rc = new_child_index_meta.init(child_index_name.c_str(), field_metas[i], false/*unique*/, true/*is_child*/);
    if (rc != RC::SUCCESS) {
      LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s", name(), index_name);
      return rc;
    }

    // 创建索引相关数据
    BplusTreeIndex *index      = new BplusTreeIndex();
    string          index_file = table_index_file(base_dir_.c_str(), name(), child_index_name.c_str());

    rc = index->create(this, index_file.c_str(), new_child_index_meta, field_metas[i]);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
      return rc;
    }

    rc = new_multi_index_meta.push_child(new_child_index_meta);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to add child index (%s) on multi-index (%s). error=%d:%s", child_index_name.c_str(), index_name, rc, strrc(rc));
      return rc;
    }

    child_indexes.push_back(index);
  }

  MultiIndex *multi_index = new MultiIndex(new_multi_index_meta);

  RecordFileScanner scanner;
  rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create scanner while creating index. table=%s, index=%s, rc=%s", name(), index_name, strrc(rc));
    return rc;
  }

  Record record;
  while (OB_SUCC(rc = scanner.next(record))) {
    for (Index *index : child_indexes) {
      rc = index->insert_entry(record.data(), &record.rid());
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
                 name(), index->index_meta().name(), strrc(rc));
        return rc;
      }
    }
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
               name(), index_name, strrc(rc));
      return rc;
    }
  }
  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_WARN("failed to insert record into index while creating index. table=%s, index=%s, rc=%s",
             name(), index_name, strrc(rc));
    return rc;
  }
  scanner.close_scan();
  LOG_INFO("inserted all records into new index. table=%s, index=%s", name(), index_name);

  indexes_.push_back(multi_index);

  for(auto index : child_indexes) {
    indexes_.push_back(index);
  }

  /// 接下来将这个索引放到表的元数据中
  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_multi_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }

  for (auto child_index_meta : new_multi_index_meta.children()) {
    rc = new_table_meta.add_index(child_index_meta);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to add child index (%s) on table (%s). error=%d:%s", child_index_meta.name(), name(), rc, strrc(rc));
      return rc;
    }
  }

  /// 内存中有一份元数据，磁盘文件也有一份元数据。修改磁盘文件时，先创建一个临时文件，写入完成后再rename为正式文件
  /// 这样可以防止文件内容不完整
  // 创建元数据临时文件
  string  tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  fstream fs;
  fs.open(tmp_file, ios_base::out | ios_base::binary | ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR_OPEN;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }
  fs.close();

  // 覆盖原始元数据文件
  string meta_file = table_meta_file(base_dir_.c_str(), name());

  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
              tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR_WRITE;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());
  return rc;
}

RC Table::delete_record(const RID &rid)
{
  RC     rc = RC::SUCCESS;
  Record record;
  rc = get_record(rid, record);
  if (OB_FAIL(rc)) {
    return rc;
  }

  return delete_record(record, nullptr);
}

RC Table::delete_record(const Record &record, Trx *trx)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {

    if (index->index_meta().is_child()) continue; // 跳过多列索引的子索引

    if (index->index_meta().children().size() > 0) {
      rc = delete_from_multi_index(record.data(), record.rid(), (MultiIndex*)index, trx);
    }
    else {
      rc = index->delete_entry(record.data(), &record.rid());
    }
    ASSERT(RC::SUCCESS == rc, 
           "failed to delete entry from index. table name=%s, index name=%s, rid=%s, rc=%s",
           name(), index->index_meta().name(), record.rid().to_string().c_str(), strrc(rc));
  }
  rc = record_handler_->delete_record(&record.rid());
  return rc;
}

RC Table::update_record(const Record &record, Trx *trx)
{
  RC rc = RC::SUCCESS;

  Record old_record;
  rc = get_record(record.rid(), old_record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get old record. table name=%s, rc=%s", name(), strrc(rc));
    return rc;
  }

  /////////////IMPORTANT/////////////
  // need to fix this function     //
  ///////////////////////////////////
  for (Index *index : indexes_) {

    if (index->index_meta().is_child()) continue; // 跳过多列索引的子索引

    if (index->index_meta().children().size() > 0) {
      rc = delete_from_multi_index(old_record.data(), old_record.rid(), (MultiIndex*)index, trx);
    }
    else {
      rc = index->delete_entry(old_record.data(), &old_record.rid());
    }
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete entry from index. table name=%s, index name=%s, rid=%s, rc=%s",
                name(), index->index_meta().name(), record.rid().to_string().c_str(), strrc(rc));
      //return rc;
    }
  }

  rc = insert_entry_of_indexes(record.data(), record.rid(), trx);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to insert entry to index. table name=%s, rc=%s", name(), strrc(rc));
    RC rc2 = insert_entry_of_indexes(old_record.data(), old_record.rid(), trx);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    return rc;
  }

  rc = record_handler_->update_record(record.rid(), record.data());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to update record. table name=%s, rc=%s", name(), strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid, Trx *trx)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {

    if (index->index_meta().is_child()) continue; // 跳过多列索引的子索引

    if (index->index_meta().children().size() > 0) {
      rc = insert_into_multi_index(record, rid, (MultiIndex*)index, trx);
    }
    else {
      rc = index->insert_entry(record, &rid);
    }

    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to insert entry to index. table name=%s, index name=%s, rc=%s",
                name(), index->index_meta().name(), strrc(rc));
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists, Trx *trx)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {

    if (index->index_meta().is_child()) continue; // 跳过多列索引的子索引

    if (index->index_meta().children().size() > 0) {
      delete_from_multi_index(record, rid, (MultiIndex*)index, trx);
    }
    else {
      rc = index->delete_entry(record, &rid);
    }

    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

RC Table::insert_into_multi_index(const char *record, const RID &rid, const MultiIndex *multi_index, Trx *trx)
{
  RC rc = RC::SUCCESS;

  if (multi_index->index_meta().unique())
  {
    RecordFileScanner scanner;

    rc = get_record_scanner(scanner, trx, ReadWriteMode::READ_ONLY);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create scanner while inserting multi-index. table=%s, index=%s, rc=%s", name(), multi_index->index_meta().name(), strrc(rc));
      return rc;
    }

    Record _record;
    bool   able_to_insert = true;
    while (OB_SUCC(rc = scanner.next(_record))) {

      if (_record.rid() == rid) {
        continue;
      }

      rc = compare_record_multi_index(record, _record.data(), multi_index, able_to_insert);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to compare record while inserting multi-index. table=%s, index=%s, rc=%s", name(), multi_index->index_meta().name(), strrc(rc));
        return rc;
      }

      if (!able_to_insert) {
        LOG_INFO("record is not able to insert into multi-index. table=%s, index=%s", name(), multi_index->index_meta().name());
        return RC::RECORD_DUPLICATE_KEY;
      }
    }
    if (RC::RECORD_EOF == rc) {
      rc = RC::SUCCESS;
    } else {
      LOG_WARN("failed to insert record into index. table=%s, index=%s, rc=%s", name(), multi_index->index_meta().name(), strrc(rc));
      return rc;
    }

    scanner.close_scan();
  }
  
  for (const IndexMeta &child_index : multi_index->index_meta().children()) {
    Index *index = find_index(child_index.name());
    if (index == nullptr) {
      LOG_ERROR("Failed to find index. table name=%s, index name=%s", name(), child_index.name());
      return RC::INTERNAL;
    }

    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to insert entry to index. table name=%s, index name=%s, rc=%s",
                name(), child_index.name(), strrc(rc));
      return rc;
    }
  }

  return rc;
}

/////////////IMPORTANT/////////////
// need to fix this function     //
///////////////////////////////////

RC Table::delete_from_multi_index(const char *record, const RID &rid, const MultiIndex *multi_index, Trx *trx)
{
  RC rc = RC::SUCCESS;

  for (const IndexMeta &child_index : multi_index->index_meta().children()) {
    Index *index = find_index(child_index.name());

    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete entry from index. table name=%s, index name=%s, rc=%s",
                name(), child_index.name(), strrc(rc));
      return rc;
    }
  }

  return rc;
}

RC Table::compare_record_multi_index(const char *former_record, const char *latter_record, const MultiIndex *multi_index, bool &result)
{
  bool result_ = false;
  for (const IndexMeta &child_index_meta : multi_index->index_meta().children()) {
    const FieldMeta *field_meta = table_meta_.field(child_index_meta.field());
    if (field_meta == nullptr) {
      LOG_ERROR("Failed to find field meta. table=%s, field=%s", name(), child_index_meta.field());
      return RC::INTERNAL;
    }

    char       *former_data = (char *)former_record + field_meta->offset();
    AttrType    former_type = field_meta->type();
    int         former_len  = field_meta->len();
    Value       former_value = Value(former_type, former_data, former_len);

    char       *latter_data = (char *)latter_record + field_meta->offset();
    AttrType    latter_type = field_meta->type();
    int         latter_len  = field_meta->len();
    Value       latter_value = Value(latter_type, latter_data, latter_len);

    bool is_equal = former_value.compare(latter_value) == 0;

    if (0 == strcmp("", former_data) && 0 == strcmp("", latter_data)) {
      is_equal = false;
    }

    // as long as one field is not equal, the two records are not equal
    if(!is_equal) {
      result_ = true;
      break;
    }
  }

  result = result_;

  return RC::SUCCESS;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}


RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {

    if (index->index_meta().children().size() > 0) continue; // 跳过多列索引

    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(),
          index->index_meta().name(),
          rc,
          strrc(rc));
      return rc;
    }
  }

  rc = data_buffer_pool_->flush_all_pages();
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

// DropTable
RC Table::destroy(const char* table_name) {
  RC rc = sync();//刷新所有脏页

  if(rc != RC::SUCCESS) return rc;

  std::string path = table_meta_file(base_dir_.c_str(), table_name);
  if(unlink(path.c_str()) != 0) {
    LOG_ERROR("Failed to remove meta file=%s, errno=%d", path.c_str(), errno);
    return RC::IOERR_ACCESS;
  }

  std::string data_path = table_data_file(base_dir_.c_str(), table_name);
  if(unlink(data_path.c_str()) != 0) {
    LOG_ERROR("Failed to remove data file=%s, errno=%d", data_path.c_str(), errno);
    return RC::IOERR_ACCESS;
  }

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {  // 清理所有的索引相关文件数据与索引元数据

    if (indexes_[i]->index_meta().children().size() > 0) continue; // 跳过多列索引

    ((BplusTreeIndex*)indexes_[i])->close();
    const IndexMeta* index_meta = table_meta_.index(i);
    std::string index_file = table_index_file(base_dir_.c_str(), table_name , index_meta->name());
    if(unlink(index_file.c_str()) != 0) {
        LOG_ERROR("Failed to remove index file=%s, errno=%d", index_file.c_str(), errno);
        return RC::IOERR_ACCESS;
    }
  }

  return RC::SUCCESS;
}
