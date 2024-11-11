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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt , BinderContext binder_context)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;

    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit , binder_context);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit , BinderContext binder_context)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }
  ExpressionBinder expression_binder(binder_context);

  vector<unique_ptr<Expression>> filter_expressions;

  unique_ptr<Expression> left_expression(condition.left_expr);
  rc = expression_binder.bind_expression(left_expression, filter_expressions);
  if(rc==RC::SCHEMA_FIELD_MISSING){
    LOG_WARN("no such field in table ");
    return rc;
  }

  unique_ptr<Expression> right_expression(condition.right_expr);
  rc = expression_binder.bind_expression(right_expression, filter_expressions);
  if(rc==RC::SCHEMA_FIELD_MISSING){
    LOG_WARN("no such field in table ");
    return rc;
  }

  filter_unit = new FilterUnit;
  if(condition.left_is_attr == 1){
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    RelAttrSqlNode* left_attr = new RelAttrSqlNode();
    left_attr->attribute_name = ((UnboundFieldExpr *)(condition.left_expr))->field_name();
    rc                     = get_table_and_field(db, default_table, tables, *left_attr, table, field);
    if (rc != RC::SUCCESS) {
      left_attr->relation_name  = ((UnboundFieldExpr *)(condition.left_expr))->table_name();
      if(left_attr->relation_name.size()<1){
      LOG_WARN("cannot find attr");
      return rc;
      }
      rc = RC::SUCCESS;
      table = db->find_table(left_attr->relation_name.c_str());
      field = table->table_meta().field(left_attr->attribute_name.c_str());

    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
    } else if(1 == condition.left_is_val){
    FilterObj filter_obj;
    ValueExpr *  left_value_expr  = static_cast<ValueExpr *>(condition.left_expr);
    const Value left_cell       = left_value_expr->get_value();
    filter_obj.init_value(left_cell);
    filter_unit->set_left(filter_obj);
    } else{
    // 通过 expr.get() 获取原始指针
    std::unique_ptr<Expression> &left_expr = filter_expressions[0];

    // Expression *raw_expr = expr.get();
    // 使用 raw_expr 进行操作
    FilterObj filter_obj;
    filter_obj.init_expr(left_expr);
    filter_unit->set_left(filter_obj);
    }

  // if (condition.left_is_attr) {
  //   Table           *table = nullptr;
  //   const FieldMeta *field = nullptr;
  //   rc                     = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
  //   if (rc != RC::SUCCESS) {
  //     LOG_WARN("cannot find attr");
  //     return rc;
  //   }
  //   FilterObj filter_obj;
  //   filter_obj.init_attr(Field(table, field));
  //   filter_unit->set_left(filter_obj);
  // }else if(condition.left_is_expr){
  //   FilterObj filter_obj;
  //   filter_obj.init_expr(condition.left_expr);
  //   filter_unit->set_left(filter_obj);
  // }
  // else {
  //   FilterObj filter_obj;
  //   filter_obj.init_value(condition.left_value);
  //   filter_unit->set_left(filter_obj);
  // }

    if(1 == condition.right_is_attr){
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    RelAttrSqlNode* right_attr = new RelAttrSqlNode();
    right_attr->attribute_name = ((UnboundFieldExpr*) (condition.right_expr))->field_name();
    rc                     = get_table_and_field(db, default_table, tables, *right_attr, table, field);
    if (rc != RC::SUCCESS) {
       right_attr->relation_name  = ((UnboundFieldExpr *)(condition.right_expr))->table_name();
      if(right_attr->relation_name.size()<1){
      LOG_WARN("cannot find attr");
      return rc;
      }
      rc = RC::SUCCESS;
      table = db->find_table(right_attr->relation_name.c_str());
      field = table->table_meta().field(right_attr->attribute_name.c_str());
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
    } else if(1 == condition.right_is_val){
    FilterObj filter_obj;
    ValueExpr *  right_value_expr  = static_cast<ValueExpr *>(condition.right_expr);
    const Value right_cell       = right_value_expr->get_value();
    filter_obj.init_value(right_cell);
    filter_unit->set_right(filter_obj);
    } else{
    // 通过索引访问 std::unique_ptr<Expression>
    std::unique_ptr<Expression> &right_expr = filter_expressions[1];
    // Expression *raw_expr = expr.get();
    FilterObj filter_obj;
    filter_obj.init_expr(right_expr);
    filter_unit->set_right(filter_obj);
    }
  // if (condition.right_is_attr) {
  //   Table           *table = nullptr;
  //   const FieldMeta *field = nullptr;
  //   rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
  //   if (rc != RC::SUCCESS) {
  //     LOG_WARN("cannot find attr");
  //     return rc;
  //   }
  //   FilterObj filter_obj;
  //   filter_obj.init_attr(Field(table, field));
  //   filter_unit->set_right(filter_obj);
  // } else if(condition.right_is_expr){
  //   FilterObj filter_obj;
  //   filter_obj.init_expr(condition.right_expr);
  //   filter_unit->set_right(filter_obj);
  // } else {
  //   FilterObj filter_obj;
  //   filter_obj.init_value(condition.right_value);
  //   filter_unit->set_right(filter_obj);
  // }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}
