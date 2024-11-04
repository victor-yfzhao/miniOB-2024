#ifndef __OBSERVER_SQL_PARSER_DROP_TABLE_STMT_H__
#define __OBSERVER_SQL_PARSER_DROP_TABLE_STMT_H__

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"

class DropTableStmt : public Stmt {
public:
    DropTableStmt(const std::string &table_name) : table_name_(table_name) {}
    virtual ~DropTableStmt() = default;

    StmtType type() const override { return StmtType::DROP_TABLE; }

    const std::string &table_name() const { return table_name_; }

    static RC create(Db* db, const DropTableSqlNode &drop_table, Stmt *&stmt);

private:
    std::string table_name_;
};

#endif // __OBSERVER_SQL_PARSER_DROP_TABLE_STMT_H__