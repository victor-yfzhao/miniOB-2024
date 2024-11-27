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
    HAVING = 263,                  /* HAVING  */
    COUNT = 264,                   /* COUNT  */
    SUM = 265,                     /* SUM  */
    MAX = 266,                     /* MAX  */
    MIN = 267,                     /* MIN  */
    AVG = 268,                     /* AVG  */
    TABLE = 269,                   /* TABLE  */
    TABLES = 270,                  /* TABLES  */
    INDEX = 271,                   /* INDEX  */
    UNIQUE = 272,                  /* UNIQUE  */
    CALC = 273,                    /* CALC  */
    SELECT = 274,                  /* SELECT  */
    DESC = 275,                    /* DESC  */
    SHOW = 276,                    /* SHOW  */
    SYNC = 277,                    /* SYNC  */
    INSERT = 278,                  /* INSERT  */
    DELETE = 279,                  /* DELETE  */
    UPDATE = 280,                  /* UPDATE  */
    LBRACE = 281,                  /* LBRACE  */
    RBRACE = 282,                  /* RBRACE  */
    LMBRACE = 283,                 /* LMBRACE  */
    RMBRACE = 284,                 /* RMBRACE  */
    COMMA = 285,                   /* COMMA  */
    TRX_BEGIN = 286,               /* TRX_BEGIN  */
    TRX_COMMIT = 287,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 288,            /* TRX_ROLLBACK  */
    NULL_T = 289,                  /* NULL_T  */
    NULLABLE = 290,                /* NULLABLE  */
    INT_T = 291,                   /* INT_T  */
    STRING_T = 292,                /* STRING_T  */
    FLOAT_T = 293,                 /* FLOAT_T  */
    VECTOR_T = 294,                /* VECTOR_T  */
    L2_DISTANCE = 295,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 296,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 297,           /* INNER_PRODUCT  */
    LENGTH = 298,                  /* LENGTH  */
    ROUND = 299,                   /* ROUND  */
    DATE_FORMAT = 300,             /* DATE_FORMAT  */
    AS = 301,                      /* AS  */
    DATE_T = 302,                  /* DATE_T  */
    HELP = 303,                    /* HELP  */
    EXIT = 304,                    /* EXIT  */
    DOT = 305,                     /* DOT  */
    INTO = 306,                    /* INTO  */
    VALUES = 307,                  /* VALUES  */
    FROM = 308,                    /* FROM  */
    JOIN = 309,                    /* JOIN  */
    INNER = 310,                   /* INNER  */
    WHERE = 311,                   /* WHERE  */
    IN_SQL = 312,                  /* IN_SQL  */
    EXISTS = 313,                  /* EXISTS  */
    ORDER = 314,                   /* ORDER  */
    ASC = 315,                     /* ASC  */
    AND = 316,                     /* AND  */
    NOT = 317,                     /* NOT  */
    IS = 318,                      /* IS  */
    LIKE_SQL = 319,                /* LIKE_SQL  */
    SET = 320,                     /* SET  */
    ON = 321,                      /* ON  */
    LOAD = 322,                    /* LOAD  */
    DATA = 323,                    /* DATA  */
    INFILE = 324,                  /* INFILE  */
    EXPLAIN = 325,                 /* EXPLAIN  */
    STORAGE = 326,                 /* STORAGE  */
    FORMAT = 327,                  /* FORMAT  */
    EQ = 328,                      /* EQ  */
    LT = 329,                      /* LT  */
    GT = 330,                      /* GT  */
    LE = 331,                      /* LE  */
    GE = 332,                      /* GE  */
    NE = 333,                      /* NE  */
    NUMBER = 334,                  /* NUMBER  */
    FLOAT = 335,                   /* FLOAT  */
    ID = 336,                      /* ID  */
    SSS = 337                      /* SSS  */
  };
  typedef enum yytokentype yytoken_kind_t;
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

#line 170 "yacc_sql.hpp"

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
