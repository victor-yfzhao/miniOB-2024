/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    COUNT = 263,                   /* COUNT  */
    SUM = 264,                     /* SUM  */
    MAX = 265,                     /* MAX  */
    MIN = 266,                     /* MIN  */
    AVG = 267,                     /* AVG  */
    TABLE = 268,                   /* TABLE  */
    TABLES = 269,                  /* TABLES  */
    INDEX = 270,                   /* INDEX  */
    UNIQUE = 271,                  /* UNIQUE  */
    CALC = 272,                    /* CALC  */
    SELECT = 273,                  /* SELECT  */
    DESC = 274,                    /* DESC  */
    SHOW = 275,                    /* SHOW  */
    SYNC = 276,                    /* SYNC  */
    INSERT = 277,                  /* INSERT  */
    DELETE = 278,                  /* DELETE  */
    UPDATE = 279,                  /* UPDATE  */
    LBRACE = 280,                  /* LBRACE  */
    RBRACE = 281,                  /* RBRACE  */
    COMMA = 282,                   /* COMMA  */
    TRX_BEGIN = 283,               /* TRX_BEGIN  */
    TRX_COMMIT = 284,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 285,            /* TRX_ROLLBACK  */
    NULL_T = 286,                  /* NULL_T  */
    INT_T = 287,                   /* INT_T  */
    STRING_T = 288,                /* STRING_T  */
    FLOAT_T = 289,                 /* FLOAT_T  */
    VECTOR_T = 290,                /* VECTOR_T  */
    DATE_T = 291,                  /* DATE_T  */
    HELP = 292,                    /* HELP  */
    EXIT = 293,                    /* EXIT  */
    DOT = 294,                     /* DOT  */
    INTO = 295,                    /* INTO  */
    VALUES = 296,                  /* VALUES  */
    FROM = 297,                    /* FROM  */
    WHERE = 298,                   /* WHERE  */
    AND = 299,                     /* AND  */
    NOT = 300,                     /* NOT  */
    LIKE_SQL = 301,                /* LIKE_SQL  */
    SET = 302,                     /* SET  */
    ON = 303,                      /* ON  */
    LOAD = 304,                    /* LOAD  */
    DATA = 305,                    /* DATA  */
    INFILE = 306,                  /* INFILE  */
    EXPLAIN = 307,                 /* EXPLAIN  */
    STORAGE = 308,                 /* STORAGE  */
    FORMAT = 309,                  /* FORMAT  */
    EQ = 310,                      /* EQ  */
    LT = 311,                      /* LT  */
    GT = 312,                      /* GT  */
    LE = 313,                      /* LE  */
    GE = 314,                      /* GE  */
    NE = 315,                      /* NE  */
    NUMBER = 316,                  /* NUMBER  */
    FLOAT = 317,                   /* FLOAT  */
    ID = 318,                      /* ID  */
    SSS = 319,                     /* SSS  */
    UMINUS = 320                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 127 "yacc_sql.y"

  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
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
  char *                                     string;
  int                                        number;
  float                                      floats;

#line 150 "yacc_sql.hpp"

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
