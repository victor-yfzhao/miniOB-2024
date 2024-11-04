// File: drop_table_stmt.cpp create by zlc in 2024-10-08
#include "common/log/log.h"
#include "common/types.h"
#include "sql/stmt/drop_table_stmt.h"
#include "event/sql_debug.h"

RC DropTableStmt::create(Db* db, const DropTableSqlNode &drop_table, Stmt *&stmt) {
    stmt = new DropTableStmt(drop_table.relation_name);
    sql_debug("drop table statement: table name %s", drop_table.relation_name.c_str());
    return RC::SUCCESS;
}