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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString UNIQUE("unique");

RC IndexMeta::init(const char *name, const FieldMeta &field, bool unique, bool is_child)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_  = name;
  field_ = field.name();
  unique_ = unique;
  is_child_ = is_child;
  return RC::SUCCESS;
}

RC IndexMeta::init_multi(const char *name, bool unique)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_   = name;
  unique_ = unique;
  return RC::SUCCESS;
}

RC IndexMeta::push_child(const IndexMeta &child)
{
  children_.push_back(child);
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME]       = name_;
  json_value[FIELD_FIELD_NAME] = field_;
  json_value[UNIQUE]         = unique_;
  json_value["is_multi_index"] = children_.size() > 0;
  json_value["is_child"] = is_child_;
  
  Json::Value children_value;
  for (const IndexMeta &child : children_) {
    Json::Value child_value;
    child.to_json(child_value);
    children_value.append(child_value);
  }
  json_value["children"] = std::move(children_value);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value  = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value = json_value[UNIQUE];

  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        name_value.asCString(), field_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!unique_value.isBool()) {
    LOG_ERROR("Unique of index [%s] is not a bool. json value=%s",
        name_value.asCString(), unique_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  const Json::Value &is_multi_index = json_value["is_multi_index"];
  if (!is_multi_index.isBool()) {
    LOG_ERROR("Deserialize index [%s]: is_multi_index is not a bool", name_value.asCString());
    return RC::INTERNAL;
  }

  const Json::Value &is_child = json_value["is_child"];
  if (!is_child.isBool()) {
    LOG_ERROR("Deserialize index [%s]: is_child is not a bool", name_value.asCString());
    return RC::INTERNAL;
  }

  const Json::Value &children_value = json_value["children"];
  if (!children_value.isArray()) {
    LOG_ERROR("Deserialize index [%s]: children is not an array", name_value.asCString());
    return RC::INTERNAL;
  }
  if(is_multi_index.asBool() && children_value.size() == 0) {
    LOG_ERROR("Deserialize index [%s]: multi-index should have children", name_value.asCString());
    return RC::INTERNAL;
  }
  if(is_multi_index.asBool()) {
    for (const Json::Value &child_value : children_value) {
      IndexMeta child;
      RC rc = from_json(table, child_value, child);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Deserialize index [%s]: failed to deserialize child index", name_value.asCString());
        return rc;
      }
      index.push_child(child);
    }
    return index.init_multi(name_value.asCString(), unique_value.asBool());
  }

  const FieldMeta *_field = table.field(field_value.asCString());
  if (!is_multi_index.isBool()) {
    if (nullptr == _field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  const FieldMeta *field = (is_multi_index.asBool()) ? new FieldMeta() : _field;

  return index.init(name_value.asCString(), *field, unique_value.asBool(), is_child.asBool());
}

const char *IndexMeta::name() const { return name_.c_str(); }

const char *IndexMeta::field() const { return field_.c_str(); }

bool IndexMeta::unique() const { return unique_; }

const std::vector<IndexMeta> &IndexMeta::children() const { return children_; }

bool IndexMeta::is_child() const { return is_child_; }

void IndexMeta::desc(ostream &os) const { os << "index name=" << name_ << ", field=" << field_; }