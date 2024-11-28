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

#include <string>

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }

  if(nullptr != having_stmt_) {
    delete having_stmt_;
    having_stmt_ = nullptr;
  }
}

void split_string(const std::string &input, std::string &part1, std::string &part2) {
    size_t pos = input.find('.');
    if (pos != std::string::npos) {
        part1 = input.substr(0, pos);
        part2 = input.substr(pos + 1);
    } else {
        part1 = input;
        part2.clear();
    }
}
RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
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
    std::string table_name1, alias;
    if (nullptr == table) {
      table = db->find_table_by_alias(table_name); 
      if (nullptr == table){ 
        split_string(table_name, table_name1, alias);
        if(alias.empty()){
          LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
          return RC::SCHEMA_TABLE_NOT_EXIST;
        } else {
        // LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
        // return RC::SCHEMA_TABLE_NOT_EXIST;
        if(db->find_table_by_alias(alias.c_str()) != nullptr){
          if (db->find_table_by_alias(alias.c_str())->name() != table_name1){
          LOG_WARN("alias already exists");
          return RC::INTERNAL;
          }
        }
        table = db->find_table(table_name1.c_str());
        db->add_table_alias(table_name1.c_str(), alias.c_str());
        }
      }
    } 
    binder_context.add_table(table);
    tables.push_back(table);
    if (alias.empty()){
      table_map.insert({table_name, table});
    } else {
      table_map.insert({table_name1, table});
      table_map.insert({alias, table});
    }
  }
  //inner join 
  std::reverse(select_sql.innerjoin.begin(), select_sql.innerjoin.end());
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
  ExpressionBinder expression_binder(binder_context, db->alias_table_map());
  
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

    FilterStmt *having_stmt = nullptr;
    rc = FilterStmt::create(db,
    default_table,
    &table_map,
    select_sql.having_conditions.data(),
    static_cast<int>(select_sql.having_conditions.size()),
    having_stmt,
    binder_context);

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  //select_stmt->sub_select_  = (SelectStmt*)sub_select;
  select_stmt->having_stmt_ = having_stmt;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}