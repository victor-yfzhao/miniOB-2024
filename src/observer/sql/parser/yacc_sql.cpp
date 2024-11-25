/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 136 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_HAVING = 8,                     /* HAVING  */
  YYSYMBOL_COUNT = 9,                      /* COUNT  */
  YYSYMBOL_SUM = 10,                       /* SUM  */
  YYSYMBOL_MAX = 11,                       /* MAX  */
  YYSYMBOL_MIN = 12,                       /* MIN  */
  YYSYMBOL_AVG = 13,                       /* AVG  */
  YYSYMBOL_TABLE = 14,                     /* TABLE  */
  YYSYMBOL_TABLES = 15,                    /* TABLES  */
  YYSYMBOL_INDEX = 16,                     /* INDEX  */
  YYSYMBOL_UNIQUE = 17,                    /* UNIQUE  */
  YYSYMBOL_CALC = 18,                      /* CALC  */
  YYSYMBOL_SELECT = 19,                    /* SELECT  */
  YYSYMBOL_DESC = 20,                      /* DESC  */
  YYSYMBOL_SHOW = 21,                      /* SHOW  */
  YYSYMBOL_SYNC = 22,                      /* SYNC  */
  YYSYMBOL_INSERT = 23,                    /* INSERT  */
  YYSYMBOL_DELETE = 24,                    /* DELETE  */
  YYSYMBOL_UPDATE = 25,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_LMBRACE = 28,                   /* LMBRACE  */
  YYSYMBOL_RMBRACE = 29,                   /* RMBRACE  */
  YYSYMBOL_COMMA = 30,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 31,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 32,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 33,              /* TRX_ROLLBACK  */
  YYSYMBOL_NULL_T = 34,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 35,                  /* NULLABLE  */
  YYSYMBOL_INT_T = 36,                     /* INT_T  */
  YYSYMBOL_STRING_T = 37,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 38,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 39,                  /* VECTOR_T  */
  YYSYMBOL_L2_DISTANCE = 40,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 41,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 42,             /* INNER_PRODUCT  */
  YYSYMBOL_DATE_T = 43,                    /* DATE_T  */
  YYSYMBOL_HELP = 44,                      /* HELP  */
  YYSYMBOL_EXIT = 45,                      /* EXIT  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_INTO = 47,                      /* INTO  */
  YYSYMBOL_VALUES = 48,                    /* VALUES  */
  YYSYMBOL_FROM = 49,                      /* FROM  */
  YYSYMBOL_JOIN = 50,                      /* JOIN  */
  YYSYMBOL_INNER = 51,                     /* INNER  */
  YYSYMBOL_WHERE = 52,                     /* WHERE  */
  YYSYMBOL_IN_SQL = 53,                    /* IN_SQL  */
  YYSYMBOL_EXISTS = 54,                    /* EXISTS  */
  YYSYMBOL_ORDER = 55,                     /* ORDER  */
  YYSYMBOL_ASC = 56,                       /* ASC  */
  YYSYMBOL_AND = 57,                       /* AND  */
  YYSYMBOL_NOT = 58,                       /* NOT  */
  YYSYMBOL_IS = 59,                        /* IS  */
  YYSYMBOL_LIKE_SQL = 60,                  /* LIKE_SQL  */
  YYSYMBOL_SET = 61,                       /* SET  */
  YYSYMBOL_ON = 62,                        /* ON  */
  YYSYMBOL_LOAD = 63,                      /* LOAD  */
  YYSYMBOL_DATA = 64,                      /* DATA  */
  YYSYMBOL_INFILE = 65,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 66,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 67,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 68,                    /* FORMAT  */
  YYSYMBOL_EQ = 69,                        /* EQ  */
  YYSYMBOL_LT = 70,                        /* LT  */
  YYSYMBOL_GT = 71,                        /* GT  */
  YYSYMBOL_LE = 72,                        /* LE  */
  YYSYMBOL_GE = 73,                        /* GE  */
  YYSYMBOL_NE = 74,                        /* NE  */
  YYSYMBOL_NUMBER = 75,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 76,                     /* FLOAT  */
  YYSYMBOL_ID = 77,                        /* ID  */
  YYSYMBOL_SSS = 78,                       /* SSS  */
  YYSYMBOL_79_ = 79,                       /* '+'  */
  YYSYMBOL_80_ = 80,                       /* '-'  */
  YYSYMBOL_81_ = 81,                       /* '*'  */
  YYSYMBOL_82_ = 82,                       /* '/'  */
  YYSYMBOL_UMINUS = 83,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 84,                  /* $accept  */
  YYSYMBOL_commands = 85,                  /* commands  */
  YYSYMBOL_command_wrapper = 86,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 87,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 88,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 89,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 90,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 91,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 92,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 93,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 94,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 95,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 96,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 97,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 98,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 99,             /* attr_def_list  */
  YYSYMBOL_attr_def = 100,                 /* attr_def  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_insert_stmt = 103,              /* insert_stmt  */
  YYSYMBOL_value_list = 104,               /* value_list  */
  YYSYMBOL_value = 105,                    /* value  */
  YYSYMBOL_vector = 106,                   /* vector  */
  YYSYMBOL_storage_format = 107,           /* storage_format  */
  YYSYMBOL_delete_stmt = 108,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 109,              /* update_stmt  */
  YYSYMBOL_kv_pair_list = 110,             /* kv_pair_list  */
  YYSYMBOL_kv_pair = 111,                  /* kv_pair  */
  YYSYMBOL_select_stmt = 112,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 113,                /* calc_stmt  */
  YYSYMBOL_expression_list = 114,          /* expression_list  */
  YYSYMBOL_expression = 115,               /* expression  */
  YYSYMBOL_rel_attr = 116,                 /* rel_attr  */
  YYSYMBOL_relation = 117,                 /* relation  */
  YYSYMBOL_rel_list = 118,                 /* rel_list  */
  YYSYMBOL_where = 119,                    /* where  */
  YYSYMBOL_condition_list = 120,           /* condition_list  */
  YYSYMBOL_condition = 121,                /* condition  */
  YYSYMBOL_comp_op = 122,                  /* comp_op  */
  YYSYMBOL_having = 123,                   /* having  */
  YYSYMBOL_inner_join_list = 124,          /* inner_join_list  */
  YYSYMBOL_inner_join = 125,               /* inner_join  */
  YYSYMBOL_group_by = 126,                 /* group_by  */
  YYSYMBOL_load_data_stmt = 127,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 128,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 129,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 130             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   469

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  139
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  282

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    81,    79,     2,    80,     2,    82,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    83
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   235,   235,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   266,   272,   277,   283,   289,   295,   301,
     308,   314,   322,   336,   353,   363,   387,   390,   403,   412,
     421,   430,   439,   448,   457,   466,   477,   480,   481,   482,
     483,   484,   487,   504,   507,   518,   522,   526,   530,   536,
     543,   548,   553,   562,   574,   577,   584,   596,   613,   619,
     632,   640,   651,   688,   697,   702,   713,   716,   719,   722,
     729,   732,   737,   743,   746,   749,   752,   756,   759,   762,
     765,   768,   771,   774,   777,   780,   783,   786,   789,   792,
     795,   798,   804,   809,   819,   824,   829,   843,   846,   852,
     855,   860,   867,   879,   890,   906,   968,   969,   970,   971,
     972,   973,   974,   975,   976,   977,   978,   979,   983,   986,
     994,   997,  1005,  1015,  1018,  1024,  1037,  1045,  1055,  1056
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "HAVING", "COUNT", "SUM", "MAX", "MIN", "AVG",
  "TABLE", "TABLES", "INDEX", "UNIQUE", "CALC", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "LMBRACE",
  "RMBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "NULL_T",
  "NULLABLE", "INT_T", "STRING_T", "FLOAT_T", "VECTOR_T", "L2_DISTANCE",
  "COSINE_DISTANCE", "INNER_PRODUCT", "DATE_T", "HELP", "EXIT", "DOT",
  "INTO", "VALUES", "FROM", "JOIN", "INNER", "WHERE", "IN_SQL", "EXISTS",
  "ORDER", "ASC", "AND", "NOT", "IS", "LIKE_SQL", "SET", "ON", "LOAD",
  "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE",
  "GE", "NE", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "drop_index_stmt", "create_table_stmt",
  "attr_def_list", "attr_def", "number", "type", "insert_stmt",
  "value_list", "value", "vector", "storage_format", "delete_stmt",
  "update_stmt", "kv_pair_list", "kv_pair", "select_stmt", "calc_stmt",
  "expression_list", "expression", "rel_attr", "relation", "rel_list",
  "where", "condition_list", "condition", "comp_op", "having",
  "inner_join_list", "inner_join", "group_by", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-188)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     336,    84,    57,   298,   298,   -54,    37,  -188,    10,    13,
      44,  -188,  -188,  -188,  -188,  -188,    48,    23,   336,   131,
     129,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,    69,    73,   124,    74,    77,   130,   134,   144,   149,
     155,   -61,  -188,   163,   164,   165,  -188,  -188,   109,  -188,
     298,  -188,  -188,  -188,   -26,  -188,   108,  -188,  -188,    81,
     101,   136,   126,   135,  -188,  -188,  -188,  -188,   173,   141,
     138,  -188,   154,     8,    96,   107,   152,   197,   192,   193,
     206,   298,   298,   298,   166,  -188,   298,   298,   298,   298,
     298,   168,   198,   188,   191,   349,   148,   194,   199,   179,
     203,  -188,   -21,  -188,    47,  -188,   174,  -188,   217,  -188,
     240,   -61,   -61,  -188,     0,   270,   340,  -188,  -188,    29,
      29,  -188,  -188,  -188,   239,   231,   266,   208,  -188,   221,
     188,   271,  -188,   255,   355,   282,   291,   241,  -188,  -188,
     298,  -188,   298,  -188,   298,  -188,   298,  -188,   298,  -188,
    -188,   298,   298,   298,   168,   273,   188,   231,   349,   305,
     370,  -188,   268,   337,  -188,   191,   313,  -188,  -188,  -188,
    -188,  -188,    11,   194,   309,   168,   311,    63,    87,   132,
     178,   224,   234,   264,   308,  -188,   168,   341,  -188,   317,
     326,  -188,    62,   304,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,   253,   208,   305,  -188,  -188,   287,   297,  -188,  -188,
     332,   282,   315,   357,   168,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,   323,   382,   387,   349,   369,   395,  -188,
    -188,  -188,   -12,   -69,  -188,   373,  -188,  -188,   374,  -188,
    -188,   335,  -188,  -188,   377,   208,   298,   208,  -188,   317,
    -188,   298,   317,   378,  -188,     9,   338,  -188,  -188,  -188,
    -188,  -188,   -69,   379,  -188,  -188,  -188,   375,   331,  -188,
    -188,  -188
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     138,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,     0,     0,    55,    56,   102,    58,
       0,    83,    81,    73,    74,    82,     0,    31,    30,     0,
       0,     0,     0,     0,   136,     1,   139,     2,     0,     0,
       0,    29,     0,     0,     0,     0,     0,     0,    61,    60,
       0,     0,     0,     0,     0,    80,     0,     0,     0,     0,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
       0,    97,     0,    98,     0,   100,     0,   101,     0,    99,
       0,     0,     0,    59,     0,     0,     0,   103,    75,    76,
      77,    78,    79,   104,   105,   130,     0,   109,    66,     0,
     107,    68,   137,     0,     0,    36,     0,     0,    34,    87,
       0,    88,     0,    90,     0,    91,     0,    89,     0,    63,
      62,     0,     0,     0,     0,     0,   107,   130,     0,     0,
       0,   108,   110,     0,    67,     0,     0,    47,    48,    49,
      50,    51,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,     0,   133,   131,    53,
       0,   124,     0,   126,   122,   116,   117,   118,   119,   120,
     121,     0,   109,     0,    70,    69,     0,     0,    43,    44,
       0,    36,    64,     0,     0,    92,    93,    95,    96,    94,
      84,    85,    86,     0,     0,   128,     0,     0,     0,   125,
     123,   127,     0,   115,   111,     0,   135,    46,     0,    45,
      37,     0,    35,    32,     0,   109,     0,   109,    72,    53,
      52,     0,    53,     0,    71,    38,     0,    33,   132,   134,
     129,    54,   113,     0,   112,    39,    40,     0,     0,   114,
      41,    65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,  -188,   392,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,   190,   233,  -188,  -188,  -188,
    -187,  -103,    -9,  -188,  -188,  -188,   242,  -188,  -166,  -188,
      -4,   -59,  -188,   218,  -156,  -135,  -161,  -188,   180,  -188,
     259,  -188,  -188,  -188,  -188,  -188,  -188
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   184,   145,   248,   182,    33,
     237,    62,    90,   252,    34,    35,   140,   141,    36,    37,
      63,    64,    65,   134,   135,   138,   171,   172,   211,   258,
     166,   167,   235,    38,    39,    40,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    95,   142,   200,    96,   174,   149,     4,   195,   150,
      97,    98,    99,   100,    88,    89,    51,    46,    47,    48,
      49,    50,    52,    67,   112,   114,   116,   118,   120,   223,
     161,   197,   124,   125,   126,   111,    51,   217,   129,   130,
     131,   132,    52,   275,   276,   218,   219,   245,    53,    54,
      55,   244,    68,    97,    98,    99,   100,    69,    97,    98,
      99,   100,    70,    56,    57,   199,    59,   277,   254,   220,
     214,    44,   271,    45,   151,   273,   263,   152,   170,    97,
      98,    99,   100,    56,    57,    58,    59,    73,    60,    61,
     225,   187,   128,   188,   268,   189,   270,   190,    41,   191,
      42,    43,   192,   193,   194,    46,    47,    48,    49,    50,
      99,   100,   159,   160,   226,   239,    46,    47,    48,    49,
      50,    71,   240,   113,    51,    72,    97,    98,    99,   100,
      52,    75,    76,   259,   115,    51,    53,    54,    55,   262,
      80,    52,    97,    98,    99,   100,    78,    53,    54,    55,
      79,    81,   243,   170,    82,    94,    83,   101,   102,   227,
      84,    46,    47,    48,    49,    50,    97,    98,    99,   100,
      85,    56,    57,    58,    59,    86,    60,    61,   103,   117,
      51,    87,    56,    57,    58,    59,    52,    60,    61,    91,
      92,    93,    53,    54,    55,   105,   170,   104,   170,   107,
     106,   153,   272,   108,   154,   228,    46,    47,    48,    49,
      50,    97,    98,    99,   100,   109,   110,    46,    47,    48,
      49,    50,   121,   122,   119,    51,   143,    56,    57,    58,
      59,    52,    60,    61,   169,   123,    51,    53,    54,    55,
     137,   147,    52,   127,   155,   133,   136,   156,    53,    54,
      55,   229,   269,    97,    98,    99,   100,    97,    98,    99,
     100,   230,    46,    47,    48,    49,    50,   157,   139,   164,
     158,   144,    56,    57,    58,    59,   146,    60,    61,   242,
     148,    51,   165,    56,    57,    58,    59,    52,    60,    61,
     173,   231,   168,    53,    54,    55,    97,    98,    99,   100,
     162,   175,   176,    97,    98,    99,   100,    46,    47,    48,
      49,    50,   183,    97,    98,    99,   100,   185,   186,    97,
      98,    99,   100,   196,     4,   212,    51,   216,    56,    57,
      58,    59,    52,    60,    61,   232,   222,   224,    53,    54,
      55,     1,     2,    97,    98,    99,   100,   236,   234,    97,
      98,    99,   100,   238,     3,     4,     5,     6,     7,     8,
       9,    10,   241,   213,   246,    51,   249,    11,    12,    13,
     163,    52,   247,    56,    57,    58,    59,    51,    60,    61,
      14,    15,   251,    52,   253,   255,   256,    97,    98,    99,
     100,   177,   178,   179,   180,   257,   260,    16,   181,    17,
     264,   265,    18,   266,   267,   274,   279,   278,   281,   280,
      74,   250,    56,    57,   233,    59,   221,   215,   261,    97,
      98,    99,   100,   201,    56,    57,   198,    59,   202,   203,
     204,     0,     0,     0,     0,     0,     0,     0,     0,   205,
     206,   207,   208,   209,   210,     0,     0,     0,   201,    97,
      98,    99,   100,   202,   203,   204,     0,     0,     0,     0,
       0,     0,     0,     0,   205,   206,   207,   208,   209,   210
};

static const yytype_int16 yycheck[] =
{
       4,    60,   105,   169,    30,   140,    27,    19,   164,    30,
      79,    80,    81,    82,    75,    76,    28,     9,    10,    11,
      12,    13,    34,    77,    83,    84,    85,    86,    87,   185,
      30,   166,    91,    92,    93,    27,    28,    26,    97,    98,
      99,   100,    34,    34,    35,    34,    35,   213,    40,    41,
      42,   212,    15,    79,    80,    81,    82,    47,    79,    80,
      81,    82,    49,    75,    76,   168,    78,    58,   224,    58,
     173,    14,   259,    16,    27,   262,   242,    30,   137,    79,
      80,    81,    82,    75,    76,    77,    78,    64,    80,    81,
      27,   150,    96,   152,   255,   154,   257,   156,    14,   158,
      16,    17,   161,   162,   163,     9,    10,    11,    12,    13,
      81,    82,   121,   122,    27,    53,     9,    10,    11,    12,
      13,    77,    60,    27,    28,    77,    79,    80,    81,    82,
      34,     0,     3,   236,    27,    28,    40,    41,    42,   242,
      16,    34,    79,    80,    81,    82,    77,    40,    41,    42,
      77,    77,   211,   212,    77,    46,    26,    49,    77,    27,
      26,     9,    10,    11,    12,    13,    79,    80,    81,    82,
      26,    75,    76,    77,    78,    26,    80,    81,    77,    27,
      28,    26,    75,    76,    77,    78,    34,    80,    81,    26,
      26,    26,    40,    41,    42,    69,   255,    61,   257,    26,
      65,    27,   261,    62,    30,    27,     9,    10,    11,    12,
      13,    79,    80,    81,    82,    77,    62,     9,    10,    11,
      12,    13,    30,    30,    27,    28,    78,    75,    76,    77,
      78,    34,    80,    81,    26,    29,    28,    40,    41,    42,
      52,    62,    34,    77,    27,    77,    48,    30,    40,    41,
      42,    27,   256,    79,    80,    81,    82,    79,    80,    81,
      82,    27,     9,    10,    11,    12,    13,    27,    77,    30,
      30,    77,    75,    76,    77,    78,    77,    80,    81,    26,
      77,    28,    51,    75,    76,    77,    78,    34,    80,    81,
      69,    27,    26,    40,    41,    42,    79,    80,    81,    82,
      30,    30,    47,    79,    80,    81,    82,     9,    10,    11,
      12,    13,    30,    79,    80,    81,    82,    26,    77,    79,
      80,    81,    82,    50,    19,    57,    28,    14,    75,    76,
      77,    78,    34,    80,    81,    27,    27,    26,    40,    41,
      42,     5,     6,    79,    80,    81,    82,    30,     7,    79,
      80,    81,    82,    27,    18,    19,    20,    21,    22,    23,
      24,    25,    58,    26,    77,    28,    34,    31,    32,    33,
      30,    34,    75,    75,    76,    77,    78,    28,    80,    81,
      44,    45,    67,    34,    27,    62,     4,    79,    80,    81,
      82,    36,    37,    38,    39,     8,    27,    61,    43,    63,
      27,    27,    66,    68,    27,    27,    27,    69,    77,    34,
      18,   221,    75,    76,   196,    78,   183,   175,   238,    79,
      80,    81,    82,    53,    75,    76,   167,    78,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    72,    73,    74,    -1,    -1,    -1,    53,    79,
      80,    81,    82,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    18,    19,    20,    21,    22,    23,    24,
      25,    31,    32,    33,    44,    45,    61,    63,    66,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,   103,   108,   109,   112,   113,   127,   128,
     129,    14,    16,    17,    14,    16,     9,    10,    11,    12,
      13,    28,    34,    40,    41,    42,    75,    76,    77,    78,
      80,    81,   105,   114,   115,   116,   114,    77,    15,    47,
      49,    77,    77,    64,    86,     0,     3,   130,    77,    77,
      16,    77,    77,    26,    26,    26,    26,    26,    75,    76,
     106,    26,    26,    26,    46,   115,    30,    79,    80,    81,
      82,    49,    77,    77,    61,    69,    65,    26,    62,    77,
      62,    27,   115,    27,   115,    27,   115,    27,   115,    27,
     115,    30,    30,    29,   115,   115,   115,    77,   114,   115,
     115,   115,   115,    77,   117,   118,    48,    52,   119,    77,
     110,   111,   105,    78,    77,   100,    77,    62,    77,    27,
      30,    27,    30,    27,    30,    27,    30,    27,    30,   106,
     106,    30,    30,    30,    30,    51,   124,   125,    26,    26,
     115,   120,   121,    69,   119,    30,    47,    36,    37,    38,
      39,    43,   102,    30,    99,    26,    77,   115,   115,   115,
     115,   115,   115,   115,   115,   118,    50,   119,   124,   105,
     112,    53,    58,    59,    60,    69,    70,    71,    72,    73,
      74,   122,    57,    26,   105,   110,    14,    26,    34,    35,
      58,   100,    27,   118,    26,    27,    27,    27,    27,    27,
      27,    27,    27,   117,     7,   126,    30,   104,    27,    53,
      60,    58,    26,   115,   120,   112,    77,    75,   101,    34,
      99,    67,   107,    27,   118,    62,     4,     8,   123,   105,
      27,   122,   105,   112,    27,    27,    68,    27,   120,   114,
     120,   104,   115,   104,    27,    34,    35,    58,    69,    27,
      34,    77
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    96,    97,    98,    99,    99,   100,   100,
     100,   100,   100,   100,   100,   100,   101,   102,   102,   102,
     102,   102,   103,   104,   104,   105,   105,   105,   105,   105,
     106,   106,   106,   106,   107,   107,   108,   109,   110,   110,
     111,   111,   112,   113,   114,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   116,   117,   118,   118,   119,   119,   120,
     120,   120,   121,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   123,   123,
     124,   124,   125,   126,   126,   127,   128,   129,   130,   130
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     9,     5,     8,     0,     3,     5,     6,
       6,     7,     2,     3,     3,     4,     1,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     1,     1,     1,     3,
       1,     1,     3,     3,     0,     4,     4,     5,     1,     3,
       3,     5,     8,     2,     1,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     6,     6,     6,     4,     4,     4,
       4,     4,     6,     6,     6,     6,     6,     3,     3,     3,
       3,     3,     1,     3,     1,     1,     3,     0,     2,     0,
       1,     3,     5,     5,     6,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     2,     0,     2,
       0,     2,     5,     0,     3,     7,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 236 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1894 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 266 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1903 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 272 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1911 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 277 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1919 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 283 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1927 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 289 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1935 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 295 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1943 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 301 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1953 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 308 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1961 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 314 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1971 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 323 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attribute_name.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      create_index.unique = false;
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 1989 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 337 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attribute_name.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      create_index.unique = true;
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2007 "yacc_sql.cpp"
    break;

  case 34: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 354 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2019 "yacc_sql.cpp"
    break;

  case 35: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 364 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2044 "yacc_sql.cpp"
    break;

  case 36: /* attr_def_list: %empty  */
#line 387 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2052 "yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 391 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2066 "yacc_sql.cpp"
    break;

  case 38: /* attr_def: ID type LBRACE number RBRACE  */
#line 404 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-3].number);
      (yyval.attr_info)->name = (yyvsp[-4].string);
      (yyval.attr_info)->length = (yyvsp[-1].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-4].string));
    }
#line 2079 "yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE NULL_T  */
#line 413 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2092 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE NULLABLE  */
#line 422 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-5].string));
    }
#line 2105 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type LBRACE number RBRACE NOT NULL_T  */
#line 431 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-5].number);
      (yyval.attr_info)->name = (yyvsp[-6].string);
      (yyval.attr_info)->length = (yyvsp[-3].number);
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-6].string));
    }
#line 2118 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type  */
#line 440 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[0].number);
      (yyval.attr_info)->name = (yyvsp[-1].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-1].string));
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type NULL_T  */
#line 449 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type NULLABLE  */
#line 458 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = true;
      free((yyvsp[-2].string));
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type NOT NULL_T  */
#line 467 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-2].number);
      (yyval.attr_info)->name = (yyvsp[-3].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = false;
      free((yyvsp[-3].string));
    }
#line 2170 "yacc_sql.cpp"
    break;

  case 46: /* number: NUMBER  */
#line 477 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2176 "yacc_sql.cpp"
    break;

  case 47: /* type: INT_T  */
#line 480 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2182 "yacc_sql.cpp"
    break;

  case 48: /* type: STRING_T  */
#line 481 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2188 "yacc_sql.cpp"
    break;

  case 49: /* type: FLOAT_T  */
#line 482 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2194 "yacc_sql.cpp"
    break;

  case 50: /* type: VECTOR_T  */
#line 483 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2200 "yacc_sql.cpp"
    break;

  case 51: /* type: DATE_T  */
#line 484 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2206 "yacc_sql.cpp"
    break;

  case 52: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 488 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2223 "yacc_sql.cpp"
    break;

  case 53: /* value_list: %empty  */
#line 504 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2231 "yacc_sql.cpp"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 507 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 518 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2254 "yacc_sql.cpp"
    break;

  case 56: /* value: FLOAT  */
#line 522 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2263 "yacc_sql.cpp"
    break;

  case 57: /* value: NULL_T  */
#line 526 "yacc_sql.y"
             {
      (yyval.value) = new Value(AttrType::NULLS, nullptr, 0);
      (yyloc) = (yylsp[0]);
    }
#line 2272 "yacc_sql.cpp"
    break;

  case 58: /* value: SSS  */
#line 530 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2283 "yacc_sql.cpp"
    break;

  case 59: /* value: LMBRACE vector RMBRACE  */
#line 536 "yacc_sql.y"
                            {
      (yyval.value) = new Value((yyvsp[-1].vector));
      delete (yyvsp[-1].vector);
    }
#line 2292 "yacc_sql.cpp"
    break;

  case 60: /* vector: FLOAT  */
#line 543 "yacc_sql.y"
          {
      (yyval.vector) = new std::vector<float>();
      (yyval.vector)->push_back((yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2302 "yacc_sql.cpp"
    break;

  case 61: /* vector: NUMBER  */
#line 548 "yacc_sql.y"
            {
      (yyval.vector) = new std::vector<float>();
      (yyval.vector)->push_back((float)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2312 "yacc_sql.cpp"
    break;

  case 62: /* vector: FLOAT COMMA vector  */
#line 553 "yacc_sql.y"
                         {
      if ((yyvsp[0].vector) != nullptr) {
        (yyval.vector) = (yyvsp[0].vector);
      } else {
        (yyval.vector) = new std::vector<float>;
      }
      (yyval.vector)->insert((yyval.vector)->begin(), (yyvsp[-2].floats));
      (yyloc) = (yylsp[-2]);
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 63: /* vector: NUMBER COMMA vector  */
#line 562 "yacc_sql.y"
                          {
      if ((yyvsp[0].vector) != nullptr) {
        (yyval.vector) = (yyvsp[0].vector);
      } else {
        (yyval.vector) = new std::vector<float>;
      }
      (yyval.vector)->insert((yyval.vector)->begin(), (float)(yyvsp[-2].number));
      (yyloc) = (yylsp[-2]);
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 64: /* storage_format: %empty  */
#line 574 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2348 "yacc_sql.cpp"
    break;

  case 65: /* storage_format: STORAGE FORMAT EQ ID  */
#line 578 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2356 "yacc_sql.cpp"
    break;

  case 66: /* delete_stmt: DELETE FROM ID where  */
#line 585 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2370 "yacc_sql.cpp"
    break;

  case 67: /* update_stmt: UPDATE ID SET kv_pair_list where  */
#line 597 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      if ((yyvsp[-1].kv_pair_list) != nullptr) {
        (yyval.sql_node)->update.kv_pairs.swap(*(yyvsp[-1].kv_pair_list));
        delete (yyvsp[-1].kv_pair_list);
      }
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
    }
#line 2388 "yacc_sql.cpp"
    break;

  case 68: /* kv_pair_list: kv_pair  */
#line 614 "yacc_sql.y"
    {
      (yyval.kv_pair_list) = new std::vector<KVPairNode>;
      (yyval.kv_pair_list)->emplace_back(*(yyvsp[0].kv_pair));
      delete (yyvsp[0].kv_pair);
    }
#line 2398 "yacc_sql.cpp"
    break;

  case 69: /* kv_pair_list: kv_pair COMMA kv_pair_list  */
#line 620 "yacc_sql.y"
    {
      if ((yyvsp[0].kv_pair_list) != nullptr) {
        (yyval.kv_pair_list) = (yyvsp[0].kv_pair_list);
      } else {
        (yyval.kv_pair_list) = new std::vector<KVPairNode>;
      }
      (yyval.kv_pair_list)->emplace_back(*(yyvsp[-2].kv_pair));
      delete (yyvsp[-2].kv_pair);
    }
#line 2412 "yacc_sql.cpp"
    break;

  case 70: /* kv_pair: ID EQ value  */
#line 633 "yacc_sql.y"
    {
      (yyval.kv_pair) = new KVPairNode;
      (yyval.kv_pair)->key = (yyvsp[-2].string);
      (yyval.kv_pair)->value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2424 "yacc_sql.cpp"
    break;

  case 71: /* kv_pair: ID EQ LBRACE select_stmt RBRACE  */
#line 641 "yacc_sql.y"
    {
      (yyval.kv_pair) = new KVPairNode;
      (yyval.kv_pair)->key = (yyvsp[-4].string);
      (yyval.kv_pair)->sub_select = &(yyvsp[-1].sql_node)->selection;
      (yyval.kv_pair)->has_sub_select = true;
      free((yyvsp[-4].string));
    }
#line 2436 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT expression_list FROM rel_list inner_join_list where group_by having  */
#line 652 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-4].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].relation_list));
        delete (yyvsp[-4].relation_list);
      }

      if((yyvsp[-3].inner_join_list) != nullptr) {
        (yyval.sql_node)->selection.innerjoin.swap(*(yyvsp[-3].inner_join_list));
        delete (yyvsp[-3].inner_join_list);
      }

      if ((yyvsp[-2].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
      }

      if ((yyvsp[-1].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }

      if((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.having_conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }

      (yyval.sql_node)->selection.sub_select = nullptr;
    }
#line 2475 "yacc_sql.cpp"
    break;

  case 73: /* calc_stmt: CALC expression_list  */
#line 689 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 74: /* expression_list: expression  */
#line 698 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2494 "yacc_sql.cpp"
    break;

  case 75: /* expression_list: expression COMMA expression_list  */
#line 703 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2507 "yacc_sql.cpp"
    break;

  case 76: /* expression: expression '+' expression  */
#line 713 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 77: /* expression: expression '-' expression  */
#line 716 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2523 "yacc_sql.cpp"
    break;

  case 78: /* expression: expression '*' expression  */
#line 719 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 79: /* expression: expression '/' expression  */
#line 722 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 80: /* expression: '-' expression  */
#line 729 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2547 "yacc_sql.cpp"
    break;

  case 81: /* expression: value  */
#line 732 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2557 "yacc_sql.cpp"
    break;

  case 82: /* expression: rel_attr  */
#line 737 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2568 "yacc_sql.cpp"
    break;

  case 83: /* expression: '*'  */
#line 743 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2576 "yacc_sql.cpp"
    break;

  case 84: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 746 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_vector_expression(VectorExpr::Type::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2584 "yacc_sql.cpp"
    break;

  case 85: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 749 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_vector_expression(VectorExpr::Type::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2592 "yacc_sql.cpp"
    break;

  case 86: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 752 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_vector_expression(VectorExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 87: /* expression: COUNT LBRACE expression RBRACE  */
#line 756 "yacc_sql.y"
                                    {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2608 "yacc_sql.cpp"
    break;

  case 88: /* expression: SUM LBRACE expression RBRACE  */
#line 759 "yacc_sql.y"
                                  { 
      (yyval.expression) = create_aggregate_expression("sum",   (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2616 "yacc_sql.cpp"
    break;

  case 89: /* expression: AVG LBRACE expression RBRACE  */
#line 762 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("avg",   (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2624 "yacc_sql.cpp"
    break;

  case 90: /* expression: MAX LBRACE expression RBRACE  */
#line 765 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("max",   (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2632 "yacc_sql.cpp"
    break;

  case 91: /* expression: MIN LBRACE expression RBRACE  */
#line 768 "yacc_sql.y"
                                  {
      (yyval.expression) = create_aggregate_expression("min",   (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 92: /* expression: COUNT LBRACE expression COMMA expression RBRACE  */
#line 771 "yacc_sql.y"
                                                     {
      (yyval.expression) = create_aggregate_expression("count", nullptr, sql_string, &(yyloc));
    }
#line 2648 "yacc_sql.cpp"
    break;

  case 93: /* expression: SUM LBRACE expression COMMA expression RBRACE  */
#line 774 "yacc_sql.y"
                                                   {
      (yyval.expression) = create_aggregate_expression("sum", nullptr, sql_string, &(yyloc));
    }
#line 2656 "yacc_sql.cpp"
    break;

  case 94: /* expression: AVG LBRACE expression COMMA expression RBRACE  */
#line 777 "yacc_sql.y"
                                                   {
      (yyval.expression) = create_aggregate_expression("avg", nullptr, sql_string, &(yyloc));
    }
#line 2664 "yacc_sql.cpp"
    break;

  case 95: /* expression: MAX LBRACE expression COMMA expression RBRACE  */
#line 780 "yacc_sql.y"
                                                   {
      (yyval.expression) = create_aggregate_expression("max", nullptr, sql_string, &(yyloc));
    }
#line 2672 "yacc_sql.cpp"
    break;

  case 96: /* expression: MIN LBRACE expression COMMA expression RBRACE  */
#line 783 "yacc_sql.y"
                                                   {
      (yyval.expression) = create_aggregate_expression("min", nullptr, sql_string, &(yyloc));
    }
#line 2680 "yacc_sql.cpp"
    break;

  case 97: /* expression: COUNT LBRACE RBRACE  */
#line 786 "yacc_sql.y"
                         {
      (yyval.expression) = create_aggregate_expression("count", nullptr, sql_string, &(yyloc));
    }
#line 2688 "yacc_sql.cpp"
    break;

  case 98: /* expression: SUM LBRACE RBRACE  */
#line 789 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("sum", nullptr, sql_string, &(yyloc));
    }
#line 2696 "yacc_sql.cpp"
    break;

  case 99: /* expression: AVG LBRACE RBRACE  */
#line 792 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("avg", nullptr, sql_string, &(yyloc));
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 100: /* expression: MAX LBRACE RBRACE  */
#line 795 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("max", nullptr, sql_string, &(yyloc));
    }
#line 2712 "yacc_sql.cpp"
    break;

  case 101: /* expression: MIN LBRACE RBRACE  */
#line 798 "yacc_sql.y"
                       {
      (yyval.expression) = create_aggregate_expression("min", nullptr, sql_string, &(yyloc));
    }
#line 2720 "yacc_sql.cpp"
    break;

  case 102: /* rel_attr: ID  */
#line 804 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2730 "yacc_sql.cpp"
    break;

  case 103: /* rel_attr: ID DOT ID  */
#line 809 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 104: /* relation: ID  */
#line 819 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2750 "yacc_sql.cpp"
    break;

  case 105: /* rel_list: relation  */
#line 824 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<std::string>();
      (yyval.relation_list)->push_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 106: /* rel_list: relation COMMA rel_list  */
#line 829 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2775 "yacc_sql.cpp"
    break;

  case 107: /* where: %empty  */
#line 843 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2783 "yacc_sql.cpp"
    break;

  case 108: /* where: WHERE condition_list  */
#line 846 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 109: /* condition_list: %empty  */
#line 852 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2799 "yacc_sql.cpp"
    break;

  case 110: /* condition_list: condition  */
#line 855 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2809 "yacc_sql.cpp"
    break;

  case 111: /* condition_list: condition AND condition_list  */
#line 860 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 112: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 867 "yacc_sql.y"
                                                  {
      (yyval.condition) = new ConditionSqlNode;
      if((yyvsp[-4].expression)->type()==ExprType::UNBOUND_FIELD){(yyval.condition)->left_is_attr = 1;}
      if((yyvsp[-4].expression)->type()==ExprType::VALUE){(yyval.condition)->left_is_val = 1;}
      (yyval.condition)->left_expr=(yyvsp[-4].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->has_sub_select = 2;
      (yyval.condition)->sub_select = &(yyvsp[-1].sql_node)->selection;
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2834 "yacc_sql.cpp"
    break;

  case 113: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 879 "yacc_sql.y"
                                                 { 
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->has_sub_select = 1;
      (yyval.condition)->sub_select = &(yyvsp[-3].sql_node)->selection;
      if((yyvsp[0].expression)->type()==ExprType::UNBOUND_FIELD){(yyval.condition)->right_is_attr = 1;}
      if((yyvsp[0].expression)->type()==ExprType::VALUE){(yyval.condition)->right_is_val = 1;}
      (yyval.condition)->right_expr=(yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 2849 "yacc_sql.cpp"
    break;

  case 114: /* condition: expression comp_op LBRACE value value_list RBRACE  */
#line 890 "yacc_sql.y"
                                                        {
      (yyval.condition) = new ConditionSqlNode;
      if((yyvsp[-5].expression)->type()==ExprType::UNBOUND_FIELD){(yyval.condition)->left_is_attr = 1;}
      if((yyvsp[-5].expression)->type()==ExprType::VALUE){(yyval.condition)->left_is_val = 1;}
      (yyval.condition)->left_expr=(yyvsp[-5].expression);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->has_sub_select = 2;
      (yyval.condition)->right_is_const = 1;
      // 
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.condition)->values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 115: /* condition: expression comp_op expression  */
#line 906 "yacc_sql.y"
                                    {
      (yyval.condition) = new ConditionSqlNode;
      if((yyvsp[-2].expression)->type()==ExprType::UNBOUND_FIELD){(yyval.condition)->left_is_attr = 1;}
      if((yyvsp[-2].expression)->type()==ExprType::VALUE){(yyval.condition)->left_is_val = 1;}
      (yyval.condition)->left_expr=(yyvsp[-2].expression);
      if((yyvsp[0].expression)->type()==ExprType::UNBOUND_FIELD){(yyval.condition)->right_is_attr = 1;}
      if((yyvsp[0].expression)->type()==ExprType::VALUE){(yyval.condition)->right_is_val = 1;}
      (yyval.condition)->right_expr=(yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      (yyval.condition)->has_sub_select = 0;
    }
#line 2886 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: EQ  */
#line 968 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2892 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: LT  */
#line 969 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2898 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: GT  */
#line 970 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2904 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: LE  */
#line 971 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2910 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: GE  */
#line 972 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2916 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: NE  */
#line 973 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2922 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: LIKE_SQL  */
#line 974 "yacc_sql.y"
               { (yyval.comp) = LIKE; }
#line 2928 "yacc_sql.cpp"
    break;

  case 123: /* comp_op: NOT LIKE_SQL  */
#line 975 "yacc_sql.y"
                   { (yyval.comp) = NOT_LIKE; }
#line 2934 "yacc_sql.cpp"
    break;

  case 124: /* comp_op: IN_SQL  */
#line 976 "yacc_sql.y"
             { (yyval.comp) = IN; }
#line 2940 "yacc_sql.cpp"
    break;

  case 125: /* comp_op: NOT IN_SQL  */
#line 977 "yacc_sql.y"
                 { (yyval.comp) = NOT_IN; }
#line 2946 "yacc_sql.cpp"
    break;

  case 126: /* comp_op: IS  */
#line 978 "yacc_sql.y"
         { (yyval.comp) = IS_NULL; }
#line 2952 "yacc_sql.cpp"
    break;

  case 127: /* comp_op: IS NOT  */
#line 979 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_NULL; }
#line 2958 "yacc_sql.cpp"
    break;

  case 128: /* having: %empty  */
#line 983 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr; 
    }
#line 2966 "yacc_sql.cpp"
    break;

  case 129: /* having: HAVING condition_list  */
#line 987 "yacc_sql.y"
    {
      (yyval.condition_list) = (yyvsp[0].condition_list); // 返回 expression_list
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 130: /* inner_join_list: %empty  */
#line 994 "yacc_sql.y"
    {
      (yyval.inner_join_list) = new std::vector<innerjoinSqlNode>;
    }
#line 2982 "yacc_sql.cpp"
    break;

  case 131: /* inner_join_list: inner_join inner_join_list  */
#line 998 "yacc_sql.y"
    {
      (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 132: /* inner_join: INNER JOIN relation ON condition_list  */
#line 1006 "yacc_sql.y"
    {
      // 创建并填充 innerjoinSqlNode
      (yyval.inner_join) = new innerjoinSqlNode;
      (yyval.inner_join)->relation  =  (yyvsp[-2].string);
      (yyval.inner_join)->conditions.swap(*(yyvsp[0].condition_list));
    }
#line 3003 "yacc_sql.cpp"
    break;

  case 133: /* group_by: %empty  */
#line 1015 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr; // 当 GROUP BY 为空时，赋值为 nullptr
    }
#line 3011 "yacc_sql.cpp"
    break;

  case 134: /* group_by: GROUP BY expression_list  */
#line 1019 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list); // 返回 expression_list
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 135: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1025 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3033 "yacc_sql.cpp"
    break;

  case 136: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1038 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3042 "yacc_sql.cpp"
    break;

  case 137: /* set_variable_stmt: SET ID EQ value  */
#line 1046 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3054 "yacc_sql.cpp"
    break;


#line 3058 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1058 "yacc_sql.y"

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
