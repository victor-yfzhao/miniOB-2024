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
    DATE_T = 298,                  /* DATE_T  */
    HELP = 299,                    /* HELP  */
    EXIT = 300,                    /* EXIT  */
    DOT = 301,                     /* DOT  */
    INTO = 302,                    /* INTO  */
    VALUES = 303,                  /* VALUES  */
    FROM = 304,                    /* FROM  */
    JOIN = 305,                    /* JOIN  */
    INNER = 306,                   /* INNER  */
    WHERE = 307,                   /* WHERE  */
    IN = 308,                      /* IN  */
    EXISTS = 309,                  /* EXISTS  */
    ORDER = 310,                   /* ORDER  */
    ASC = 311,                     /* ASC  */
    AND = 312,                     /* AND  */
    NOT = 313,                     /* NOT  */
    IS = 314,                      /* IS  */
    LIKE_SQL = 315,                /* LIKE_SQL  */
    SET = 316,                     /* SET  */
    ON = 317,                      /* ON  */
    LOAD = 318,                    /* LOAD  */
    DATA = 319,                    /* DATA  */
    INFILE = 320,                  /* INFILE  */
    EXPLAIN = 321,                 /* EXPLAIN  */
    STORAGE = 322,                 /* STORAGE  */
    FORMAT = 323,                  /* FORMAT  */
    EQ = 324,                      /* EQ  */
    LT = 325,                      /* LT  */
    GT = 326,                      /* GT  */
    LE = 327,                      /* LE  */
    GE = 328,                      /* GE  */
    NE = 329,                      /* NE  */
    NUMBER = 330,                  /* NUMBER  */
    FLOAT = 331,                   /* FLOAT  */
    ID = 332,                      /* ID  */
    SSS = 333,                     /* SSS  */
    UMINUS = 334                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 152 "yacc_sql.y"

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
