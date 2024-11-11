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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  SelectSqlNode *sub_select_node = select_sql.sub_select;
  Stmt          *sub_select      = nullptr;
  if (nullptr != sub_select_node) {
    if (select_sql.conditions.size() != 1) {
      LOG_WARN("sub select should have only one condition");
      return RC::INVALID_ARGUMENT;
    }

    RelAttrSqlNode sub_select_field;
    sub_select_field.relation_name = sub_select_node->relations[0];
    if (sub_select_node->expressions.size() != 1) {
      LOG_WARN("sub select should have only one field");
      return RC::INVALID_ARGUMENT;
    }
    if (sub_select_node->expressions[0]->type() != ExprType::UNBOUND_FIELD && sub_select_node->expressions[0]->type() != ExprType::UNBOUND_AGGREGATION) {
      LOG_WARN("sub select field should be a field");
      return RC::INVALID_ARGUMENT;
    }
    sub_select_field.attribute_name = sub_select_node->expressions[0]->name();

    if (select_sql.conditions[0].left_is_attr) {
      select_sql.conditions[0].right_is_attr = 1;
      select_sql.conditions[0].right_attr.relation_name = sub_select_field.relation_name;
      select_sql.conditions[0].right_attr.attribute_name = sub_select_field.attribute_name;
    }else{
      select_sql.conditions[0].left_is_attr = 1;
      select_sql.conditions[0].left_attr.relation_name = sub_select_field.relation_name;
      select_sql.conditions[0].left_attr.attribute_name = sub_select_field.attribute_name;
    }

    RC rc_sub = SelectStmt::create(db, *sub_select_node, sub_select);
    if (rc_sub != RC::SUCCESS) {
      LOG_WARN("create sub select stmt failed. rc=%s", strrc(rc_sub));
      return rc_sub;
    }
  }

  BinderContext binder_context;

  
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;

  // collect tables in `from` statement
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
  }
  //inner join 
  for (size_t i = 0; i < select_sql.innerjoin.size(); i++) {
    innerjoinSqlNode tmp = select_sql.innerjoin[i];

    const char *table_name = tmp.relation.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
    for ( ConditionSqlNode condition : tmp.conditions){
      select_sql.conditions.emplace_back(condition);
    }

    
  }

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt,
      binder_context);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->sub_select_  = (SelectStmt*)sub_select;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}
