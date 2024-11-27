
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

VectorExpr *create_vector_expression(VectorExpr::Type type,
                                     Expression *left,
                                     Expression *right,
                                     const char *sql_string,
                                     YYLTYPE *llocp)
{
  VectorExpr *expr = new VectorExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

FunctionExpr * create_function_expression(FunctionExpr::Type type,
                                          Expression *args,
                                          int round_accuracy,
                                          std::string date_format,
                                          const char *sql_string,
                                          YYLTYPE *llocp)
{
  if(type == FunctionExpr::Type::ROUND) {
    FunctionExpr *expr = new FunctionExpr(type, args , round_accuracy);
    expr->set_name(token_name(sql_string, llocp));
    return expr;
  }
  else if (type == FunctionExpr::Type::DATE_FORMAT) {
    FunctionExpr *expr = new FunctionExpr(type, args , date_format);
    expr->set_name(token_name(sql_string, llocp));
    return expr;
  }else{
  FunctionExpr *expr = new FunctionExpr(type, args);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
  }
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        GROUP
        HAVING //ADD HAVING
        COUNT // ADD COUNT
        SUM //ADD SUM
        MAX //ADD MAX
        MIN //ADD MIN
        AVG //ADD AVG
        TABLE
        TABLES
        INDEX
        UNIQUE // ADD UNIQUE
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        LMBRACE
        RMBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        NULL_T // ADD NULL
        NULLABLE // ADD NULLABLE
        INT_T
        STRING_T
        FLOAT_T
        VECTOR_T
        L2_DISTANCE
        COSINE_DISTANCE
        INNER_PRODUCT
        LENGTH
        ROUND
        DATE_FORMAT
        AS
        DATE_T // ADD DATE
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        JOIN
        INNER
        WHERE
        IN_SQL
        EXISTS
        ORDER
        ASC
        AND
        NOT // ADD NOT
        IS // ADD IS
        LIKE_SQL // ADD LIKE
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        EQ
        LT
        GT
        LE
        GE
        NE

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  innerjoinSqlNode  *                        inner_join;
  std::vector<innerjoinSqlNode> *            inner_join_list;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  KVPairNode *                               kv_pair;
  std::vector<KVPairNode> *                  kv_pair_list;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  std::vector<float> *                       vector;
  char *                                     string;
  int                                        number;
  float                                      floats;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <string>              alias
%type <number>              type
%type <condition>           condition
%type <condition_list>      having
%type <value>               value
%type <number>              number
%type <string>              relation
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <inner_join_list>     inner_join_list
%type <inner_join>          inner_join
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <string>              storage_format
%type <relation_list>       rel_list
%type <kv_pair>             kv_pair
%type <kv_pair_list>        kv_pair_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <vector>              vector
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
// %nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      if ($7 != nullptr) {
        create_index.attribute_name.swap(*$7);
        delete $7;
      }
      create_index.unique = false;
      free($3);
      free($5);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE rel_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      if ($8 != nullptr) {
        create_index.attribute_name.swap(*$8);
        delete $8;
      }
      create_index.unique = true;
      free($4);
      free($6);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE 
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = false;
      free($1);
    }
    | ID type LBRACE number RBRACE NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = true;
      free($1);
    }
    | ID type LBRACE number RBRACE NULLABLE
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = true;
      free($1);
    }
    | ID type LBRACE number RBRACE NOT NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = false;
      free($1);
    }
    | ID type
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = false;
      free($1);
    }
    | ID type NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = true;
      free($1);
    }
    | ID type NULLABLE
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = true;
      free($1);
    }
    | ID type NOT NULL_T
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = false;
      free($1);
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    | DATE_T   { $$ = static_cast<int>(AttrType::DATES); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    | NULL_T {
      $$ = new Value(AttrType::NULLS, nullptr, 0);
      @$ = @1;
    }
    | SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    | LMBRACE vector RMBRACE{
      $$ = new Value($2);
      delete $2;
    }
    ;

vector:
    FLOAT {
      $$ = new std::vector<float>();
      $$->push_back($1);
      @$ = @1;
    }
    |NUMBER {
      $$ = new std::vector<float>();
      $$->push_back((float)$1);
      @$ = @1;
    }
    | FLOAT COMMA vector {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<float>;
      }
      $$->insert($$->begin(), $1);
      @$ = @1;
    }
    | NUMBER COMMA vector {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<float>;
      }
      $$->insert($$->begin(), (float)$1);
      @$ = @1;
    }
    ;
storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET kv_pair_list where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      if ($4 != nullptr) {
        $$->update.kv_pairs.swap(*$4);
        delete $4;
      }
      if ($5 != nullptr) {
        $$->update.conditions.swap(*$5);
        delete $5;
      }
      free($2);
    }
    ;

kv_pair_list:
    kv_pair
    {
      $$ = new std::vector<KVPairNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | kv_pair COMMA kv_pair_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<KVPairNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

kv_pair:
    ID EQ value
    {
      $$ = new KVPairNode;
      $$->key = $1;
      $$->value = *$3;
      free($1);
      delete $3;
    }
    | ID EQ LBRACE select_stmt RBRACE
    {
      $$ = new KVPairNode;
      $$->key = $1;
      $$->sub_select = &$4->selection;
      $$->has_sub_select = true;
      free($1);
    }
    ;
  
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list 
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    |
    SELECT expression_list FROM rel_list inner_join_list where group_by having 
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($4 != nullptr) {
        $$->selection.relations.swap(*$4);
        delete $4;
      }

      if($5 != nullptr) {
        $$->selection.innerjoin.swap(*$5);
        delete $5;
      }

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }

      if ($7 != nullptr) {
        $$->selection.group_by.swap(*$7);
        delete $7;
      }

      if($8 != nullptr) {
        $$->selection.having_conditions.swap(*$8);
        delete $8;
      }

      $$->selection.sub_select = nullptr;
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

alias:
    /* empty */ {
      $$ = nullptr;
    }
    | ID {
      $$ = $1;
    }
    | AS ID {
      $$ = $2;
    }

expression_list:
    expression alias
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      if (nullptr != $2) {
        $1->set_alias($2);
      }
      $$->emplace_back($1);
    }
    | expression alias COMMA expression_list
    {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      if (nullptr != $2) {
        $1->set_alias($2);
      }
      $$->emplace($$->begin(), $1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      if ($1 == nullptr) {
        $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $3, nullptr, sql_string, &@$);
      } else {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    // | '-' expression %prec UMINUS {
    //   $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    // }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    | ID DOT '*'  {
      $$ = new StarExpr($1);
      free($1);
    }
    | L2_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = create_vector_expression(VectorExpr::Type::L2_DISTANCE, $3, $5, sql_string, &@$);
    }
    | COSINE_DISTANCE LBRACE expression COMMA expression RBRACE {
      $$ = create_vector_expression(VectorExpr::Type::COSINE_DISTANCE, $3, $5, sql_string, &@$);
    }
    | INNER_PRODUCT LBRACE expression COMMA expression RBRACE {
      $$ = create_vector_expression(VectorExpr::Type::INNER_PRODUCT, $3, $5, sql_string, &@$);
    }
    | LENGTH LBRACE expression RBRACE {
      $$ = create_function_expression(FunctionExpr::Type::LENGTH, $3, -1 , "" , sql_string, &@$);
    }
    | ROUND LBRACE expression COMMA NUMBER RBRACE {
      $$ = create_function_expression(FunctionExpr::Type::ROUND, $3, $5 , "" , sql_string, &@$);
    }
    | DATE_FORMAT LBRACE expression COMMA SSS RBRACE {
      $$ = create_function_expression(FunctionExpr::Type::DATE_FORMAT, $3, -1 , $5, sql_string, &@$);
    }
    // your code here
    | COUNT LBRACE expression RBRACE{
      $$ = create_aggregate_expression("count", $3, sql_string, &@$);
    }
    | SUM LBRACE expression RBRACE{ 
      $$ = create_aggregate_expression("sum",   $3, sql_string, &@$);
    }
    | AVG LBRACE expression RBRACE{
      $$ = create_aggregate_expression("avg",   $3, sql_string, &@$);
    }
    | MAX LBRACE expression RBRACE{
      $$ = create_aggregate_expression("max",   $3, sql_string, &@$);
    }
    | MIN LBRACE expression RBRACE{
      $$ = create_aggregate_expression("min",   $3, sql_string, &@$);
    }
    | COUNT LBRACE expression COMMA expression RBRACE{
      $$ = create_aggregate_expression("count", nullptr, sql_string, &@$);
    }
    | SUM LBRACE expression COMMA expression RBRACE{
      $$ = create_aggregate_expression("sum", nullptr, sql_string, &@$);
    }
    | AVG LBRACE expression COMMA expression RBRACE{
      $$ = create_aggregate_expression("avg", nullptr, sql_string, &@$);
    }
    | MAX LBRACE expression COMMA expression RBRACE{
      $$ = create_aggregate_expression("max", nullptr, sql_string, &@$);
    }
    | MIN LBRACE expression COMMA expression RBRACE{
      $$ = create_aggregate_expression("min", nullptr, sql_string, &@$);
    }
    | COUNT LBRACE RBRACE{
      $$ = create_aggregate_expression("count", nullptr, sql_string, &@$);
    }
    | SUM LBRACE RBRACE{
      $$ = create_aggregate_expression("sum", nullptr, sql_string, &@$);
    }
    | AVG LBRACE RBRACE{
      $$ = create_aggregate_expression("avg", nullptr, sql_string, &@$);
    }
    | MAX LBRACE RBRACE{
      $$ = create_aggregate_expression("max", nullptr, sql_string, &@$);
    }
    | MIN LBRACE RBRACE{
      $$ = create_aggregate_expression("min", nullptr, sql_string, &@$);
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;
rel_list:
    relation alias{
      $$ = new std::vector<std::string>();
      if ($2 != nullptr) {
        $$->push_back(std::string($1) + '.' + std::string($2));
        free($1);
        free($2);
      } else {
      $$->push_back($1);
      free($1);
      }
    }
    | relation alias COMMA rel_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::string>;
      }
      if ($2 != nullptr) {
        $$->insert($$->begin(), std::string($1) + '.' + std::string($2));
        free($1);
        free($2);
      } else {
        $$->insert($$->begin(), $1);
        free($1);
      }
      // $$->insert($$->begin(), $1);
      // free($1);
    }
    ;

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
     expression comp_op LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      if($1->type()==ExprType::UNBOUND_FIELD){$$->left_is_attr = 1;}
      if($1->type()==ExprType::VALUE){$$->left_is_val = 1;}
      $$->left_expr=$1;
      $$->right_is_attr = 0;
      $$->has_sub_select = 2;
      $$->sub_select = &$4->selection;
      $$->comp = $2;
    } 
    
    | 
    LBRACE select_stmt RBRACE comp_op expression { 
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->has_sub_select = 1;
      $$->sub_select = &$2->selection;
      if($5->type()==ExprType::UNBOUND_FIELD){$$->right_is_attr = 1;}
      if($5->type()==ExprType::VALUE){$$->right_is_val = 1;}
      $$->right_expr=$5;
      $$->comp = $4;
    } 
    // const value
    | expression comp_op LBRACE value value_list RBRACE {
      $$ = new ConditionSqlNode;
      if($1->type()==ExprType::UNBOUND_FIELD){$$->left_is_attr = 1;}
      if($1->type()==ExprType::VALUE){$$->left_is_val = 1;}
      $$->left_expr=$1;
      $$->right_is_attr = 0;
      $$->has_sub_select = 2;
      $$->right_is_const = 1;
      // 
      if ($5 != nullptr) {
        $$->values.swap(*$5);
        delete $5;
      }
      $$->values.emplace_back(*$4);
      $$->comp = $2;
    } 
    | expression comp_op expression {
      $$ = new ConditionSqlNode;
      if($1->type()==ExprType::UNBOUND_FIELD){$$->left_is_attr = 1;}
      if($1->type()==ExprType::VALUE){$$->left_is_val = 1;}
      $$->left_expr=$1;
      if($3->type()==ExprType::UNBOUND_FIELD){$$->right_is_attr = 1;}
      if($3->type()==ExprType::VALUE){$$->right_is_val = 1;}
      $$->right_expr=$3;
      $$->comp = $2;
      $$->has_sub_select = 0;
    }
    /* | rel_attr IS NULL_T
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = Value(AttrType::NULLS, nullptr, 0);
      $$->comp = IS_NULL;
      $$->has_sub_select = 0;

      delete $1;
    }
    | rel_attr IS NOT NULL_T
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 0;
      $$->right_value = Value(AttrType::NULLS, nullptr, 0);
      $$->comp = IS_NOT_NULL;
      $$->has_sub_select = 0;

      delete $1;
    }
    | value IS NULL_T
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = Value(AttrType::NULLS, nullptr, 0);
      $$->comp = IS_NULL;
      $$->has_sub_select = 0;

      delete $1;
    }
    | value IS NOT NULL_T
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 0;
      $$->left_value = *$1;
      $$->right_is_attr = 0;
      $$->right_value = Value(AttrType::NULLS, nullptr, 0);
      $$->comp = IS_NOT_NULL;
      $$->has_sub_select = 0;

      delete $1;
    } */
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE_SQL { $$ = LIKE; }
    | NOT LIKE_SQL { $$ = NOT_LIKE; }
    | IN_SQL { $$ = IN; }
    | NOT IN_SQL { $$ = NOT_IN; }
    | IS { $$ = IS_NULL; }
    | IS NOT { $$ = IS_NOT_NULL; }
    ;
having:
    /* empty */
    {
      $$ = nullptr; 
    }
    | HAVING condition_list
    {
      $$ = $2; // 返回 expression_list
    }
    ;
// your code here

inner_join_list:
    {
      $$ = new std::vector<innerjoinSqlNode>;
    }
    | inner_join inner_join_list
    {
      $$ = $2;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
inner_join:
    INNER JOIN relation ON condition_list
    {
      // 创建并填充 innerjoinSqlNode
      $$ = new innerjoinSqlNode;
      $$->relation  =  $3;
      $$->conditions.swap(*$5);
    }
    ;
group_by:
    /* empty */
    {
      $$ = nullptr; // 当 GROUP BY 为空时，赋值为 nullptr
    }
    | GROUP BY expression_list
    {
      $$ = $3; // 返回 expression_list
    }
    ;
load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
