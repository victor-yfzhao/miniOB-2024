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
// Created by Wangyunlai on 2023/4/25.
//

#include "sql/executor/create_index_executor.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/create_index_stmt.h"
#include "storage/table/table.h"

RC CreateIndexExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_INDEX,
      "create index executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  CreateIndexStmt *create_index_stmt = static_cast<CreateIndexStmt *>(stmt);

  Trx   *trx   = session->current_trx();
  Table *table = create_index_stmt->table();
  RC     rc    = RC::SUCCESS;

  if (create_index_stmt->field_metas().size() == 1){
    const FieldMeta *field_meta = &create_index_stmt->field_metas()[0];
    rc = table->create_index(trx, field_meta, create_index_stmt->index_name().c_str(), create_index_stmt->unique());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create index. table=%s, index=%s, field=%s, rc=%s",
                table->name(), create_index_stmt->index_name().c_str(), field_meta->name(), strrc(rc));
      return rc;
    }
  } 
  
  else {
    rc = table->create_multi_index(trx, create_index_stmt->field_metas(), create_index_stmt->index_name().c_str(), create_index_stmt->unique());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create index. table=%s, index=%s, rc=%s",
                table->name(), create_index_stmt->index_name().c_str(), strrc(rc));
      return rc;
    }
  }

  // for(size_t i = 0; i < create_index_stmt->field_metas().size(); i++) {
  //   const FieldMeta *field_meta = &create_index_stmt->field_metas()[i];

  //   string index_name = create_index_stmt->index_name() + "_" + std::to_string(i);
    
  //   rc = table->create_index(trx, field_meta, index_name.c_str(), create_index_stmt->unique());
  //   if (rc != RC::SUCCESS) {
  //     LOG_ERROR("Failed to create index. table=%s, index=%s, field=%s, rc=%s",
  //               table->name(), create_index_stmt->index_name().c_str(), field_meta->name(), strrc(rc));
  //     return rc;
  //   }
  // }

  // rc = table->create_index(trx, create_index_stmt->field_metas(), create_index_stmt->index_name().c_str(), create_index_stmt->unique());

  return rc;
}