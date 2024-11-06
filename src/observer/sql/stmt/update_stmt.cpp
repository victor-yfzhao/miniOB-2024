/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt)
    : table_(table), filter_stmt_(filter_stmt) {}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check whether the condition argument is valid
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  vector<unique_ptr<Expression>> filter_expressions;
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt , filter_expressions);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  UpdateStmt *stmt_tmp = new UpdateStmt(table, filter_stmt);
  
  // check whether the field exists
  TableMeta table_meta = table->table_meta();
  for (KVPairNode kv_pair : update.kv_pairs) {
    const FieldMeta *field = table_meta.field(kv_pair.key.c_str());

    if (nullptr == field) {
      LOG_WARN("no such field in table: table %s, field %s", table->name(), kv_pair.key.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    const Value *_value = new Value(kv_pair.value);

    stmt_tmp->kv_pairs_.insert(std::pair<std::string, const Value *>(kv_pair.key, _value));
  }
  
  stmt = stmt_tmp;

  return RC::SUCCESS;
}
