/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    BY = 259,
    AS = 260,
    CREATE = 261,
    DROP = 262,
    GROUP = 263,
    HAVING = 264,
    COUNT = 265,
    SUM = 266,
    MAX = 267,
    MIN = 268,
    AVG = 269,
    TABLE = 270,
    TABLES = 271,
    INDEX = 272,
    UNIQUE = 273,
    CALC = 274,
    SELECT = 275,
    DESC = 276,
    SHOW = 277,
    SYNC = 278,
    INSERT = 279,
    DELETE = 280,
    UPDATE = 281,
    LBRACE = 282,
    RBRACE = 283,
    LMBRACE = 284,
    RMBRACE = 285,
    COMMA = 286,
    TRX_BEGIN = 287,
    TRX_COMMIT = 288,
    TRX_ROLLBACK = 289,
    NULL_T = 290,
    NULLABLE = 291,
    INT_T = 292,
    STRING_T = 293,
    FLOAT_T = 294,
    VECTOR_T = 295,
    L2_DISTANCE = 296,
    COSINE_DISTANCE = 297,
    INNER_PRODUCT = 298,
    LENGTH = 299,
    ROUND = 300,
    DATE_FORMAT = 301,
    DATE_T = 302,
    HELP = 303,
    EXIT = 304,
    DOT = 305,
    INTO = 306,
    VALUES = 307,
    FROM = 308,
    JOIN = 309,
    INNER = 310,
    WHERE = 311,
    IN_SQL = 312,
    EXISTS = 313,
    ORDER = 314,
    ASC = 315,
    AND = 316,
    NOT = 317,
    IS = 318,
    LIKE_SQL = 319,
    SET = 320,
    ON = 321,
    LOAD = 322,
    DATA = 323,
    INFILE = 324,
    EXPLAIN = 325,
    STORAGE = 326,
    FORMAT = 327,
    EQ = 328,
    LT = 329,
    GT = 330,
    LE = 331,
    GE = 332,
    NE = 333,
    NUMBER = 334,
    FLOAT = 335,
    ID = 336,
    SSS = 337,
    UMINUS = 338
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 179 "yacc_sql.y"

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

#line 165 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
