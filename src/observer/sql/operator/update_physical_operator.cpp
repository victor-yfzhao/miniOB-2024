#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

// UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, const Value *values, int value_amount, FieldMeta *field)
//     : table_(table), values_(values), value_amount_(value_amount), field_(field)
// {}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  child->close();

  for (const Record &record : records_) {
    Record new_record = Record();
    new_record.copy_data(record.data(), record.len());
    new_record.set_rid(record.rid().page_num, record.rid().slot_num);

    for (const auto &kv_pair : kv_pairs_) {
      const Value *value;

      if (kv_pair.second->type() == ExprType::VALUE) {
        ValueExpr *value_expr = static_cast<ValueExpr *>(kv_pair.second.get());
        value = &value_expr->get_value();
      } 
      else if (kv_pair.second->type() ==ExprType::SUB_SELECT) {
        SubSelectExpr *sub_select_expr = static_cast<SubSelectExpr *>(kv_pair.second.get());
        if (sub_select_expr->sub_select_result().empty()) {
          RC rc_sub = sub_select_expr->set_sub_select_result();
          if (rc_sub != RC::SUCCESS) {
            LOG_WARN("failed to set sub select result: %s", strrc(rc_sub));
            return rc_sub;
          }
        }

        vector<Value> &sub_select_result = sub_select_expr->sub_select_result();

        if (sub_select_result.size() != 1) {
          LOG_WARN("sub select result size is not 1: %d", sub_select_result.size());
          return RC::INTERNAL;
        }

        if (sub_select_result.size() == 0){
          value = new Value(AttrType::NULLS, nullptr, 0);
        }
        else {
          value = &sub_select_result[0];
        }
      }


      const FieldMeta *field = table_->table_meta().field(kv_pair.first.c_str());
      if (nullptr == field) {
        LOG_WARN("no such field in table: %s", kv_pair.first.c_str());
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }

      if (strcmp(field->name(), "_null_tag") == 0) {
        continue;
      }

      AttrType attr_type = field->type();
      bool    nullable  = field->nullable();

      if (nullable) {
        const FieldMeta *null_tag_field = table_->table_meta().field("_null_tag");
        Value            null_tag_value;
        rc = set_value_from_record(new_record.data(), null_tag_field, null_tag_value);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to get value from record: %s", strrc(rc));
          return rc;
        }

        string null_tag_str = null_tag_value.to_string();

        int null_index = null_tag_str.length() - (null_tag_field->field_id() - field->field_id()) - 1;

        if (value->attr_type() == AttrType::NULLS) {
          null_tag_str[null_index] = '1';

          Value new_null_tag_value;
          new_null_tag_value.set_type(AttrType::CHARS);
          new_null_tag_value.set_data(null_tag_str.c_str(), null_tag_str.length());

          rc = set_value_to_record(new_record.data(), new_null_tag_value, null_tag_field);
          if (rc != RC::SUCCESS) {
            LOG_WARN("failed to set value to record: %s", strrc(rc));
            return rc;
          }

          continue;
        }
        
        null_tag_str[null_index] = '0';

        Value new_null_tag_value;
        new_null_tag_value.set_type(AttrType::CHARS);
        new_null_tag_value.set_data(null_tag_str.c_str(), null_tag_str.length());

        rc = set_value_to_record(new_record.data(), new_null_tag_value, null_tag_field);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to set value to record: %s", strrc(rc));
          return rc;
        }
      }

      if (attr_type != value->attr_type()) {
        Value real_value;
        rc = Value::cast_to(*value, attr_type, real_value);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to cast value: %s", strrc(rc));
          return rc;
        }
        rc = set_value_to_record(new_record.data(), real_value, field);
      } else {
        Value _value = *value;
        rc = set_value_to_record(new_record.data(), _value, field);
      }

      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to set value to record: %s", strrc(rc));
        return rc;
      }
    }
    rc = trx_->update_record(table_, new_record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to update record: %s", strrc(rc));
        return rc;
      }
  }

  return RC::SUCCESS;
}

/**
 * @brief change record's value to new value
 */
RC UpdatePhysicalOperator::set_value_to_record(char *record_data, const Value &value, const FieldMeta *field)
{
  size_t       copy_len = field->len();
  const size_t data_len = value.length();
  if (field->type() == AttrType::CHARS) {
    if (copy_len > data_len) {
      copy_len = data_len + 1;
    }
  }
  memcpy(record_data + field->offset(), value.data(), copy_len);
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::set_value_from_record(const char *record_data, const FieldMeta *field, Value &value)
{
  size_t copy_len = field->len();
  if (field->type() == AttrType::CHARS) {
    //copy_len++;
  }

  value.set_type(field->type());
  value.set_data(record_data + field->offset(), copy_len);

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  return RC::SUCCESS;
}