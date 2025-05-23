/* A Bison parser, made by GNU Bison 3.7.5.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bison_symtable.h"
#include "alpha_tokens.h"
#include "icode.h"
#include "backpatch.h"

extern int alpha_yylex();
#define yylex alpha_yylex

extern int yylineno;
extern char* yytext;

extern int yyparse();
extern FILE* yyin;

int yyerror(const char* yaccProvidedMessage);
void printError(const char* format, ...);

int scope = 0;
int loop_counter = 0;
int func_counter = 0;
int is_not_member = 0;
int anonymous_counter = 0;

#line 99 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_FUNCTION = 7,                   /* FUNCTION  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_BREAK = 9,                      /* BREAK  */
  YYSYMBOL_CONTINUE = 10,                  /* CONTINUE  */
  YYSYMBOL_AND = 11,                       /* AND  */
  YYSYMBOL_OR = 12,                        /* OR  */
  YYSYMBOL_NOT = 13,                       /* NOT  */
  YYSYMBOL_TRUE = 14,                      /* TRUE  */
  YYSYMBOL_FALSE = 15,                     /* FALSE  */
  YYSYMBOL_NIL = 16,                       /* NIL  */
  YYSYMBOL_LOCAL = 17,                     /* LOCAL  */
  YYSYMBOL_ASSIGN = 18,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 19,                      /* PLUS  */
  YYSYMBOL_MINUS = 20,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 21,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 22,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 23,                    /* MODULO  */
  YYSYMBOL_EQUAL = 24,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 25,                 /* NOT_EQUAL  */
  YYSYMBOL_GREATER_THAN = 26,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN = 27,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_EQUAL = 28,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 29,                /* LESS_EQUAL  */
  YYSYMBOL_INCREMENT = 30,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 31,                 /* DECREMENT  */
  YYSYMBOL_BRACKET_OPEN = 32,              /* BRACKET_OPEN  */
  YYSYMBOL_BRACKET_CLOSE = 33,             /* BRACKET_CLOSE  */
  YYSYMBOL_CURLY_BRACKET_OPEN = 34,        /* CURLY_BRACKET_OPEN  */
  YYSYMBOL_CURLY_BRACKET_CLOSE = 35,       /* CURLY_BRACKET_CLOSE  */
  YYSYMBOL_SQUARE_BRACKET_OPEN = 36,       /* SQUARE_BRACKET_OPEN  */
  YYSYMBOL_SQUARE_BRACKET_CLOSE = 37,      /* SQUARE_BRACKET_CLOSE  */
  YYSYMBOL_COMMA = 38,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 39,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 40,                     /* COLON  */
  YYSYMBOL_DOUBLE_COLON = 41,              /* DOUBLE_COLON  */
  YYSYMBOL_DOT = 42,                       /* DOT  */
  YYSYMBOL_DOUBLE_DOT = 43,                /* DOUBLE_DOT  */
  YYSYMBOL_OTHER = 44,                     /* OTHER  */
  YYSYMBOL_IDENTIFIER = 45,                /* IDENTIFIER  */
  YYSYMBOL_STRING_TOKEN = 46,              /* STRING_TOKEN  */
  YYSYMBOL_INTCONST = 47,                  /* INTCONST  */
  YYSYMBOL_FLOATCONST = 48,                /* FLOATCONST  */
  YYSYMBOL_IFX = 49,                       /* IFX  */
  YYSYMBOL_UMINUS = 50,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_stmts = 53,                     /* stmts  */
  YYSYMBOL_stmt = 54,                      /* stmt  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_56_2 = 56,                      /* $@2  */
  YYSYMBOL_57_3 = 57,                      /* $@3  */
  YYSYMBOL_expr = 58,                      /* expr  */
  YYSYMBOL_term = 59,                      /* term  */
  YYSYMBOL_assignexpr = 60,                /* assignexpr  */
  YYSYMBOL_primary = 61,                   /* primary  */
  YYSYMBOL_lvalue = 62,                    /* lvalue  */
  YYSYMBOL_member = 63,                    /* member  */
  YYSYMBOL_call = 64,                      /* call  */
  YYSYMBOL_callsuffix = 65,                /* callsuffix  */
  YYSYMBOL_normcall = 66,                  /* normcall  */
  YYSYMBOL_methodcall = 67,                /* methodcall  */
  YYSYMBOL_elist = 68,                     /* elist  */
  YYSYMBOL_objectdef = 69,                 /* objectdef  */
  YYSYMBOL_indexed = 70,                   /* indexed  */
  YYSYMBOL_indexedelem = 71,               /* indexedelem  */
  YYSYMBOL_block = 72,                     /* block  */
  YYSYMBOL_73_4 = 73,                      /* $@4  */
  YYSYMBOL_funcdef = 74,                   /* funcdef  */
  YYSYMBOL_75_5 = 75,                      /* $@5  */
  YYSYMBOL_76_6 = 76,                      /* $@6  */
  YYSYMBOL_identifiers = 77,               /* identifiers  */
  YYSYMBOL_const = 78,                     /* const  */
  YYSYMBOL_idlist = 79,                    /* idlist  */
  YYSYMBOL_ifstmt = 80,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 81,                 /* whilestmt  */
  YYSYMBOL_82_7 = 82,                      /* $@7  */
  YYSYMBOL_forstmt = 83,                   /* forstmt  */
  YYSYMBOL_84_8 = 84,                      /* $@8  */
  YYSYMBOL_returnstmt = 85                 /* returnstmt  */
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
typedef yytype_uint8 yy_state_t;

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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   604

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    74,    75,    79,    80,    81,    82,    83,
      84,    84,    85,    85,    86,    87,    88,    88,    89,    93,
      98,   105,   112,   120,   128,   136,   144,   152,   160,   166,
     172,   178,   184,   190,   197,   198,   199,   205,   206,   207,
     208,   209,   213,   229,   230,   231,   232,   233,   237,   256,
     267,   275,   279,   280,   281,   282,   286,   287,   288,   293,
     294,   298,   302,   306,   307,   308,   312,   313,   317,   318,
     322,   327,   327,   331,   331,   331,   336,   349,   359,   360,
     361,   362,   363,   364,   368,   369,   378,   391,   393,   399,
     398,   406,   405,   412,   413
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "OR", "NOT",
  "TRUE", "FALSE", "NIL", "LOCAL", "ASSIGN", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "MODULO", "EQUAL", "NOT_EQUAL", "GREATER_THAN", "LESS_THAN",
  "GREATER_EQUAL", "LESS_EQUAL", "INCREMENT", "DECREMENT", "BRACKET_OPEN",
  "BRACKET_CLOSE", "CURLY_BRACKET_OPEN", "CURLY_BRACKET_CLOSE",
  "SQUARE_BRACKET_OPEN", "SQUARE_BRACKET_CLOSE", "COMMA", "SEMICOLON",
  "COLON", "DOUBLE_COLON", "DOT", "DOUBLE_DOT", "OTHER", "IDENTIFIER",
  "STRING_TOKEN", "INTCONST", "FLOATCONST", "IFX", "UMINUS", "$accept",
  "program", "stmts", "stmt", "$@1", "$@2", "$@3", "expr", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "objectdef", "indexed", "indexedelem",
  "block", "$@4", "funcdef", "$@5", "$@6", "identifiers", "const",
  "idlist", "ifstmt", "whilestmt", "$@7", "forstmt", "$@8", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
#endif

#define YYPACT_NINF (-50)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -50,     7,   173,   -50,   -16,   -14,   -11,     3,   209,    -1,
      18,   253,   -50,   -50,   -50,    14,   253,   111,   111,   101,
     -50,   245,   -50,    48,   -50,   -50,   -50,   -50,   -50,   306,
     -50,   -50,   -50,   421,   -50,     5,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   253,   253,   253,   -50,    31,   -50,
     327,    49,   -50,   -50,   -50,   -50,   -50,   100,   -31,    49,
     -31,   466,    80,   -50,   253,   523,    -7,     8,   -50,   -50,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   -50,   253,   -50,   -50,   253,   253,    66,
      74,   -50,   -50,   -50,   253,   253,   253,    77,   485,   504,
      58,   -50,   -50,   -50,   -50,    90,   -50,    92,    19,   284,
     -50,   253,   -50,    91,   553,   542,    78,    78,   -50,   -50,
     -50,   564,   564,   575,   575,   575,   575,   523,   -25,   390,
     -50,    95,   348,   -23,   409,   -50,   173,   -50,   253,    84,
      92,   253,   -50,   253,   523,   -50,   -50,   -50,   253,   -50,
     -50,   -50,   126,   173,   369,   -50,    23,    50,   447,    51,
     -50,   173,   -50,   253,   -50,    94,   -50,   -50,   -50,   -50,
      57,   106,   -50,   -50,   -50,   173,   -50
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,    77,     0,     0,
       0,     0,    82,    83,    81,     0,     0,     0,     0,     0,
      71,    65,    18,     0,    48,    80,    79,    78,     3,     0,
      33,    19,    41,    43,    51,    44,    45,    14,    15,    47,
       6,     7,     8,     9,     0,     0,    65,    76,     0,    94,
       0,    44,    10,    12,    36,    49,    35,     0,    37,     0,
      39,     0,     0,     4,     0,    63,     0,     0,    68,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     0,    38,    40,    65,     0,     0,
       0,    57,    59,    60,     0,    65,     0,     0,     0,     0,
       0,    73,    93,    11,    13,     0,    34,    46,     0,     0,
      66,     0,    67,     0,    21,    20,    32,    31,    30,    29,
      28,    22,    23,    27,    25,    26,    24,    42,     0,     0,
      52,     0,     0,     0,     0,    54,     0,    89,     0,    84,
       0,    65,    72,     0,    64,    69,    61,    53,    65,    16,
      56,    55,    87,     0,     0,    85,     0,     0,     0,     0,
      17,     0,    90,    65,    74,     0,    58,    70,    62,    88,
       0,     0,    86,    91,    75,     0,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -50,   -50,    72,   -49,   -50,   -50,   -50,    -2,   -50,   -50,
     -50,    85,   -50,     2,   -50,   -50,   -50,   -43,   -50,   -50,
      32,   -27,   -50,   -17,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,   -50,   -50
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    28,   103,   104,   160,    65,    30,    31,
      32,    33,    34,    51,    91,    92,    93,    66,    36,    67,
      68,    37,    63,    38,   139,   171,    48,    39,   156,    40,
      41,   153,    42,   175,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    87,    62,   100,    35,    88,    50,     3,   146,    54,
     150,    89,    90,   111,    56,   111,    44,    61,    45,    59,
      59,    46,     4,    94,     5,     6,     7,     8,     9,    10,
     110,   111,    11,    12,    13,    14,    15,    95,    52,    16,
     105,    96,    98,    99,   128,   112,   113,    97,    47,    17,
      18,    19,   133,    20,   142,    21,   164,    53,    22,    55,
      23,   165,   109,   101,    24,    25,    26,    27,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,    95,   127,   166,   168,    96,   129,   152,   111,   111,
     173,    97,   132,    69,   134,   111,   111,   138,   157,    74,
      75,    76,    58,    60,   162,   159,    29,     7,     7,   144,
      35,   130,   169,   107,    11,    12,    13,    14,    15,   131,
     170,    16,   135,   140,   141,    64,   176,   148,    15,   155,
     161,    17,    18,    19,    29,   108,   154,    21,    35,   172,
      20,   158,    23,    57,   174,   145,    24,    25,    26,    27,
       0,    29,    23,     0,     0,    35,    24,     0,     0,    29,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,     0,     4,    35,     5,     6,
       7,     8,     9,    10,     0,     0,    11,    12,    13,    14,
      15,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,    18,    19,     0,    20,     0,    21,
       0,     0,    22,     0,    23,     0,     0,     0,    24,    25,
      26,    27,    11,    12,    13,    14,    15,     0,     0,    16,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      18,    19,     0,     0,     0,    21,     0,     0,    49,     0,
      23,     0,     0,     0,    24,    25,    26,    27,    11,    12,
      13,    14,    15,     0,     0,    16,    11,    12,    13,    14,
      15,     0,     0,    16,     0,    17,    18,    19,     0,    64,
       0,    21,     0,    17,    18,    19,    23,     0,     0,    21,
      24,    25,    26,    27,    23,    70,    71,     0,    24,    25,
      26,    27,     0,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,     0,    70,    71,     0,
       0,     0,     0,     0,   143,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,     0,    70,    71,
       0,     0,     0,     0,     0,    83,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     0,     0,    70,
      71,     0,     0,     0,     0,     0,   102,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,     0,     0,
      70,    71,     0,     0,     0,     0,     0,   149,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    70,    71,     0,     0,     0,     0,     0,   163,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      70,    71,     0,     0,     0,     0,     0,   147,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
       0,     0,     0,     0,     0,     0,   151,     0,     0,     0,
       0,    85,    86,    87,     0,     0,     0,    88,    70,    71,
       0,     0,     0,    89,    90,     0,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    70,    71,     0,
       0,     0,   167,     0,     0,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    70,    71,     0,   106,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    70,    71,     0,   136,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    70,    71,     0,   137,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    70,     0,     0,     0,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,    81,    82,    72,    73,    74,    75,    76,     0,
       0,    -1,    -1,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
       2,    32,    19,    46,     2,    36,     8,     0,    33,    11,
      33,    42,    43,    38,    16,    38,    32,    19,    32,    17,
      18,    32,     3,    18,     5,     6,     7,     8,     9,    10,
      37,    38,    13,    14,    15,    16,    17,    32,    39,    20,
      57,    36,    44,    45,    87,    37,    38,    42,    45,    30,
      31,    32,    95,    34,    35,    36,    33,    39,    39,    45,
      41,    38,    64,    32,    45,    46,    47,    48,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    32,    84,    33,    33,    36,    88,   136,    38,    38,
      33,    42,    94,    45,    96,    38,    38,    39,   141,    21,
      22,    23,    17,    18,   153,   148,   108,     7,     7,   111,
     108,    45,   161,    33,    13,    14,    15,    16,    17,    45,
     163,    20,    45,    33,    32,    34,   175,    32,    17,    45,
       4,    30,    31,    32,   136,    63,   138,    36,   136,    45,
      34,   143,    41,    32,   171,   113,    45,    46,    47,    48,
      -1,   153,    41,    -1,    -1,   153,    45,    -1,    -1,   161,
      -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   175,    -1,    -1,     3,   175,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    -1,    34,    -1,    36,
      -1,    -1,    39,    -1,    41,    -1,    -1,    -1,    45,    46,
      47,    48,    13,    14,    15,    16,    17,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    -1,    -1,    -1,    36,    -1,    -1,    39,    -1,
      41,    -1,    -1,    -1,    45,    46,    47,    48,    13,    14,
      15,    16,    17,    -1,    -1,    20,    13,    14,    15,    16,
      17,    -1,    -1,    20,    -1,    30,    31,    32,    -1,    34,
      -1,    36,    -1,    30,    31,    32,    41,    -1,    -1,    36,
      45,    46,    47,    48,    41,    11,    12,    -1,    45,    46,
      47,    48,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    -1,    -1,    40,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    39,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    39,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      11,    12,    -1,    -1,    -1,    -1,    -1,    39,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    39,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      11,    12,    -1,    -1,    -1,    -1,    -1,    37,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    30,    31,    32,    -1,    -1,    -1,    36,    11,    12,
      -1,    -1,    -1,    42,    43,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    11,    12,    -1,
      -1,    -1,    35,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    11,    12,    -1,    33,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    11,    12,    -1,    33,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    11,    12,    -1,    33,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    28,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     3,     5,     6,     7,     8,     9,
      10,    13,    14,    15,    16,    17,    20,    30,    31,    32,
      34,    36,    39,    41,    45,    46,    47,    48,    54,    58,
      59,    60,    61,    62,    63,    64,    69,    72,    74,    78,
      80,    81,    83,    85,    32,    32,    32,    45,    77,    39,
      58,    64,    39,    39,    58,    45,    58,    32,    62,    64,
      62,    58,    74,    73,    34,    58,    68,    70,    71,    45,
      11,    12,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    39,    18,    30,    31,    32,    36,    42,
      43,    65,    66,    67,    18,    32,    36,    42,    58,    58,
      68,    32,    39,    55,    56,    74,    33,    33,    53,    58,
      37,    38,    37,    38,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    68,    58,
      45,    45,    58,    68,    58,    45,    33,    33,    39,    75,
      33,    32,    35,    40,    58,    71,    33,    37,    32,    39,
      33,    37,    54,    82,    58,    45,    79,    68,    58,    68,
      57,     4,    54,    39,    33,    38,    33,    35,    33,    54,
      68,    76,    45,    33,    72,    84,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      55,    54,    56,    54,    54,    54,    57,    54,    54,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    61,    61,    61,    61,    61,    62,    62,
      62,    62,    63,    63,    63,    63,    64,    64,    64,    65,
      65,    66,    67,    68,    68,    68,    69,    69,    70,    70,
      71,    73,    72,    75,    76,    74,    77,    77,    78,    78,
      78,    78,    78,    78,    79,    79,    79,    80,    80,    82,
      81,    84,    83,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       0,     3,     0,     3,     1,     1,     0,     5,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     2,     2,     2,     2,     2,
       2,     1,     3,     1,     1,     1,     3,     1,     1,     2,
       2,     1,     3,     4,     3,     4,     4,     2,     6,     1,
       1,     3,     5,     1,     3,     0,     3,     3,     1,     3,
       5,     0,     4,     0,     0,     8,     1,     0,     1,     1,
       1,     1,     1,     1,     0,     1,     3,     5,     7,     0,
       6,     0,    10,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
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
    goto yyexhaustedlab;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmts  */
#line 71 "parser.y"
               {printf("program starting here: %d\n",yylineno);}
#line 1390 "parser.c"
    break;

  case 3: /* stmts: stmts stmt  */
#line 74 "parser.y"
               {printf("stmts stmt: %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1396 "parser.c"
    break;

  case 4: /* stmts: %empty  */
#line 75 "parser.y"
     {printf("Empty stmt: %d\n",yylineno);}
#line 1402 "parser.c"
    break;

  case 5: /* stmt: expr SEMICOLON  */
#line 79 "parser.y"
                   {printf("expr SEMICOLON: %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1408 "parser.c"
    break;

  case 6: /* stmt: ifstmt  */
#line 80 "parser.y"
             {printf("ifstmt: %d\n",yylineno); (yyval.statementVal)=(yyvsp[0].statementVal);}
#line 1414 "parser.c"
    break;

  case 7: /* stmt: whilestmt  */
#line 81 "parser.y"
                {printf("whilestmt: %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1420 "parser.c"
    break;

  case 8: /* stmt: forstmt  */
#line 82 "parser.y"
              {printf("forstmt: %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1426 "parser.c"
    break;

  case 9: /* stmt: returnstmt  */
#line 83 "parser.y"
                 {printf("returnstmt: %d\n",yylineno); (yyval.statementVal)=(yyvsp[0].statementVal);}
#line 1432 "parser.c"
    break;

  case 10: /* $@1: %empty  */
#line 84 "parser.y"
                      { if (loop_counter==0) printError("Use of 'break' while not in a loop"); }
#line 1438 "parser.c"
    break;

  case 11: /* stmt: BREAK SEMICOLON $@1  */
#line 84 "parser.y"
                                                                                                 {printf("break semicolon : %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1444 "parser.c"
    break;

  case 12: /* $@2: %empty  */
#line 85 "parser.y"
                         { if (loop_counter==0) printError("Use of 'continue' while not in a loop"); }
#line 1450 "parser.c"
    break;

  case 13: /* stmt: CONTINUE SEMICOLON $@2  */
#line 85 "parser.y"
                                                                                                       {printf("continue semicolon : %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1456 "parser.c"
    break;

  case 14: /* stmt: block  */
#line 86 "parser.y"
            {printf("block : %d\n",yylineno); (yyval.statementVal)=(yyvsp[0].statementVal);}
#line 1462 "parser.c"
    break;

  case 15: /* stmt: funcdef  */
#line 87 "parser.y"
              {printf("funcdef : %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1468 "parser.c"
    break;

  case 16: /* $@3: %empty  */
#line 88 "parser.y"
                                 { printError("Grammar error: Function call is not lvalue"); }
#line 1474 "parser.c"
    break;

  case 17: /* stmt: call ASSIGN expr SEMICOLON $@3  */
#line 88 "parser.y"
                                                                                               {printf("call assign expr semicolon : %d\n",yylineno);}
#line 1480 "parser.c"
    break;

  case 18: /* stmt: SEMICOLON  */
#line 89 "parser.y"
                 {printf("semicolon : %d\n",yylineno); (yyval.statementVal)=create_statement();}
#line 1486 "parser.c"
    break;

  case 19: /* expr: assignexpr  */
#line 93 "parser.y"
               {
        is_not_member = 1;
        (yyval.exprVal) = (yyvsp[0].exprVal);
        printf("assignexpr: %d\n", yylineno);
    }
#line 1496 "parser.c"
    break;

  case 20: /* expr: expr OR expr  */
#line 98 "parser.y"
                 {
        printf("expr or expr : %d\n", yylineno);
        backpatch((yyvsp[-2].exprVal)->falselist, nextquadlabel());
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = mergelists((yyvsp[-2].exprVal)->truelist, (yyvsp[0].exprVal)->truelist);
        (yyval.exprVal)->falselist = (yyvsp[0].exprVal)->falselist;
    }
#line 1508 "parser.c"
    break;

  case 21: /* expr: expr AND expr  */
#line 105 "parser.y"
                  {
        printf("expr and expr : %d\n", yylineno);
        backpatch((yyvsp[-2].exprVal)->truelist, nextquadlabel());
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = (yyvsp[0].exprVal)->truelist;
        (yyval.exprVal)->falselist = mergelists((yyvsp[-2].exprVal)->falselist, (yyvsp[0].exprVal)->falselist);
    }
#line 1520 "parser.c"
    break;

  case 22: /* expr: expr EQUAL expr  */
#line 112 "parser.y"
                    {
        printf("expr equal expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = newlist(nextquadlabel());
        (yyval.exprVal)->falselist = newlist(nextquadlabel() + 1);
        emit(if_eq, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
#line 1533 "parser.c"
    break;

  case 23: /* expr: expr NOT_EQUAL expr  */
#line 120 "parser.y"
                        {
        printf("expr not_equal expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = newlist(nextquadlabel());
        (yyval.exprVal)->falselist = newlist(nextquadlabel() + 1);
        emit(if_noteq, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
#line 1546 "parser.c"
    break;

  case 24: /* expr: expr LESS_EQUAL expr  */
#line 128 "parser.y"
                         {
        printf("expr less_equal expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = newlist(nextquadlabel());
        (yyval.exprVal)->falselist = newlist(nextquadlabel() + 1);
        emit(if_lesseq, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
#line 1559 "parser.c"
    break;

  case 25: /* expr: expr LESS_THAN expr  */
#line 136 "parser.y"
                        {
        printf("expr less_than expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = newlist(nextquadlabel());
        (yyval.exprVal)->falselist = newlist(nextquadlabel() + 1);
        emit(if_less, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
#line 1572 "parser.c"
    break;

  case 26: /* expr: expr GREATER_EQUAL expr  */
#line 144 "parser.y"
                            {
        printf("expr greater_equal expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = newlist(nextquadlabel());
        (yyval.exprVal)->falselist = newlist(nextquadlabel() + 1);
        emit(if_greatereq, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
#line 1585 "parser.c"
    break;

  case 27: /* expr: expr GREATER_THAN expr  */
#line 152 "parser.y"
                           {
        printf("expr greater_than expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = newlist(nextquadlabel());
        (yyval.exprVal)->falselist = newlist(nextquadlabel() + 1);
        emit(if_greater, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
#line 1598 "parser.c"
    break;

  case 28: /* expr: expr MODULO expr  */
#line 160 "parser.y"
                     {
        printf("expr modulo expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(mod, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), (yyval.exprVal), 0, yylineno);
    }
#line 1609 "parser.c"
    break;

  case 29: /* expr: expr DIVIDE expr  */
#line 166 "parser.y"
                     {
        printf("expr divide expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(div_i, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), (yyval.exprVal), 0, yylineno);
    }
#line 1620 "parser.c"
    break;

  case 30: /* expr: expr MULTIPLY expr  */
#line 172 "parser.y"
                       {
        printf("expr multiply expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(mul, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), (yyval.exprVal), 0, yylineno);
    }
#line 1631 "parser.c"
    break;

  case 31: /* expr: expr MINUS expr  */
#line 178 "parser.y"
                    {
        printf("expr minus expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(sub, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), (yyval.exprVal), 0, yylineno);
    }
#line 1642 "parser.c"
    break;

  case 32: /* expr: expr PLUS expr  */
#line 184 "parser.y"
                   {
        printf("expr plus expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(add, (yyvsp[-2].exprVal), (yyvsp[0].exprVal), (yyval.exprVal), 0, yylineno);
    }
#line 1653 "parser.c"
    break;

  case 33: /* expr: term  */
#line 190 "parser.y"
         {
        (yyval.exprVal) = (yyvsp[0].exprVal);
        printf("term : %d\n", yylineno);
    }
#line 1662 "parser.c"
    break;

  case 34: /* term: BRACKET_OPEN expr BRACKET_CLOSE  */
#line 197 "parser.y"
                                    { printf("bracket_open expr bracket_close : %d\n", yylineno); }
#line 1668 "parser.c"
    break;

  case 35: /* term: MINUS expr  */
#line 198 "parser.y"
                                    { printf("minus expr : %d\n", yylineno); }
#line 1674 "parser.c"
    break;

  case 36: /* term: NOT expr  */
#line 199 "parser.y"
               {
        (yyval.exprVal) = newexpr(boolexpr_e);
        (yyval.exprVal)->truelist = (yyvsp[0].exprVal)->falselist;
        (yyval.exprVal)->falselist = (yyvsp[0].exprVal)->truelist;
        printf("not expr : %d\n", yylineno);
    }
#line 1685 "parser.c"
    break;

  case 37: /* term: INCREMENT lvalue  */
#line 205 "parser.y"
                                    { printf("increment lvalue : %d\n", yylineno); }
#line 1691 "parser.c"
    break;

  case 38: /* term: lvalue INCREMENT  */
#line 206 "parser.y"
                                    { printf("lvalue increment : %d\n", yylineno); }
#line 1697 "parser.c"
    break;

  case 39: /* term: DECREMENT lvalue  */
#line 207 "parser.y"
                                    { printf("decrement lvalue : %d\n", yylineno); }
#line 1703 "parser.c"
    break;

  case 40: /* term: lvalue DECREMENT  */
#line 208 "parser.y"
                                    { printf("lvalue decrement : %d\n", yylineno); }
#line 1709 "parser.c"
    break;

  case 41: /* term: primary  */
#line 209 "parser.y"
                                    { printf("primary : %d\n", yylineno);  (yyval.exprVal) = (yyvsp[0].exprVal);}
#line 1715 "parser.c"
    break;

  case 42: /* assignexpr: lvalue ASSIGN expr  */
#line 213 "parser.y"
                      {
        printf("lvalue ASSIGN expr %d\n", yylineno);
        Symbol_t* s = SymTable_lookup((yyvsp[-2].exprVal)->sym->name, scope);
        if(s && (s->type==USER_FUNC || s->type==LIB_FUNC) && is_not_member)
            printError("Using %s '%s' as an lvalue", (s->type==LIB_FUNC)?"LibFunc":"ProgramFunc", (yyvsp[-2].exprVal));

        //if ($3->truelist || $3->falselist) {
        //    $3 = make_bool_expr($3);
        //}

        emit(assign, (yyvsp[0].exprVal), NULL, (yyvsp[-2].exprVal), 0, yylineno);
        (yyval.exprVal) = newtemp();
        emit(assign, (yyvsp[-2].exprVal), NULL, (yyval.exprVal), 0, yylineno);
    }
#line 1734 "parser.c"
    break;

  case 43: /* primary: lvalue  */
#line 229 "parser.y"
                            {printf("lvalue : %d\n",yylineno);}
#line 1740 "parser.c"
    break;

  case 44: /* primary: call  */
#line 230 "parser.y"
                            {printf("call : %d\n",yylineno);}
#line 1746 "parser.c"
    break;

  case 45: /* primary: objectdef  */
#line 231 "parser.y"
                            {printf("objectdef : %d\n",yylineno);}
#line 1752 "parser.c"
    break;

  case 46: /* primary: BRACKET_OPEN funcdef BRACKET_CLOSE  */
#line 232 "parser.y"
                                         { (yyval.exprVal) = NULL;  printf("bracket_open funcdef bracket_close : %d\n",yylineno);}
#line 1758 "parser.c"
    break;

  case 47: /* primary: const  */
#line 233 "parser.y"
                            {printf("const : %d\n",yylineno); (yyval.exprVal) = (yyvsp[0].exprVal);}
#line 1764 "parser.c"
    break;

  case 48: /* lvalue: IDENTIFIER  */
#line 237 "parser.y"
               {
        Symbol_t* s;
        int temp_scope = scope;
        while(temp_scope >= 0){
            s = SymTable_lookup((yyvsp[0].strVal),temp_scope);
            if(s) break;
            temp_scope--;
        }
        if(s && (s->type==USER_FUNC || s->type==LIB_FUNC) && is_not_member){
            printError("Using %s '%s' as an lvalue", (s->type==LIB_FUNC)?"LibFunc":"ProgramFunc", (yyvsp[0].strVal));
        }else if (s && s->type != LIB_FUNC && s->scope != 0 && s->scope < scope && s->scope < func_counter){
            printError("Cannot access '%s' identifier that is located before function", (yyvsp[0].strVal));
        }else if(!s){
            SymTable_insert((yyvsp[0].strVal), (scope==0)?GLOBAL_VAR:LOCAL_VAR, scope, yylineno);}
        
        (yyval.exprVal) = newexpr(var_e);
        (yyval.exprVal)->sym = SymTable_lookup((yyvsp[0].strVal),scope);
        printf("identifier : %d\n",yylineno);
    }
#line 1788 "parser.c"
    break;

  case 49: /* lvalue: LOCAL IDENTIFIER  */
#line 256 "parser.y"
                       {
        if(SymTable_lookupGlobal((yyvsp[0].strVal)) && SymTable_lookupGlobal((yyvsp[0].strVal))->type == LIB_FUNC)
            printError("Collision with '%s' library function", (yyvsp[0].strVal));
        else if(!SymTable_lookup((yyvsp[0].strVal), scope)) {
            SymTable_insert((yyvsp[0].strVal), (scope==0)?GLOBAL_VAR:LOCAL_VAR, scope, yylineno); 
        }
        
        (yyval.exprVal) = newexpr(var_e);
        (yyval.exprVal)->sym = SymTable_lookup((yyvsp[0].strVal), scope);
        printf("local identifier : %d\n",yylineno);
    }
#line 1804 "parser.c"
    break;

  case 50: /* lvalue: DOUBLE_COLON IDENTIFIER  */
#line 267 "parser.y"
                              {
        if(!SymTable_lookupGlobal((yyvsp[0].strVal)))
            printError("No global variable '::%s' exists", (yyvsp[0].strVal));
        
        (yyval.exprVal) = newexpr(var_e);
        (yyval.exprVal)->sym = SymTable_lookupGlobal((yyvsp[0].strVal));
        printf("double_colon identifier : %d\n",yylineno);
    }
#line 1817 "parser.c"
    break;

  case 51: /* lvalue: member  */
#line 275 "parser.y"
             { (yyval.exprVal) = (yyvsp[0].exprVal); printf("member : %d\n",yylineno);}
#line 1823 "parser.c"
    break;

  case 52: /* member: lvalue DOT IDENTIFIER  */
#line 279 "parser.y"
                          { printf("lvalue DOT IDENTIFIER : %d\n", yylineno); }
#line 1829 "parser.c"
    break;

  case 53: /* member: lvalue SQUARE_BRACKET_OPEN expr SQUARE_BRACKET_CLOSE  */
#line 280 "parser.y"
                                                           { printf("lvalue [ expr ] : %d\n", yylineno); }
#line 1835 "parser.c"
    break;

  case 54: /* member: call DOT IDENTIFIER  */
#line 281 "parser.y"
                          {is_not_member = 0; printf("call DOT IDENTIFIER : %d\n", yylineno); }
#line 1841 "parser.c"
    break;

  case 55: /* member: call SQUARE_BRACKET_OPEN expr SQUARE_BRACKET_CLOSE  */
#line 282 "parser.y"
                                                         { printf("call [ expr ] : %d\n", yylineno); }
#line 1847 "parser.c"
    break;

  case 56: /* call: call BRACKET_OPEN elist BRACKET_CLOSE  */
#line 286 "parser.y"
                                          { printf("call ( elist ) : %d\n", yylineno); }
#line 1853 "parser.c"
    break;

  case 57: /* call: lvalue callsuffix  */
#line 287 "parser.y"
                        { printf("lvalue callsuffix : %d\n", yylineno); }
#line 1859 "parser.c"
    break;

  case 58: /* call: BRACKET_OPEN funcdef BRACKET_CLOSE BRACKET_OPEN elist BRACKET_CLOSE  */
#line 288 "parser.y"
                                                                          { printf("( funcdef )( elist ) : %d\n", yylineno); }
#line 1865 "parser.c"
    break;

  case 59: /* callsuffix: normcall  */
#line 293 "parser.y"
             { printf("normcall : %d\n", yylineno); }
#line 1871 "parser.c"
    break;

  case 60: /* callsuffix: methodcall  */
#line 294 "parser.y"
                 { printf("methodcall : %d\n", yylineno); }
#line 1877 "parser.c"
    break;

  case 61: /* normcall: BRACKET_OPEN elist BRACKET_CLOSE  */
#line 298 "parser.y"
                                     { printf("normcall ( elist ) : %d\n", yylineno); }
#line 1883 "parser.c"
    break;

  case 62: /* methodcall: DOUBLE_DOT IDENTIFIER BRACKET_OPEN elist BRACKET_CLOSE  */
#line 302 "parser.y"
                                                           { printf("methodcall ..IDENTIFIER( elist ) : %d\n", yylineno); }
#line 1889 "parser.c"
    break;

  case 63: /* elist: expr  */
#line 306 "parser.y"
         { printf("elist expr : %d\n", yylineno); }
#line 1895 "parser.c"
    break;

  case 64: /* elist: elist COMMA expr  */
#line 307 "parser.y"
                       { printf("elist , expr : %d\n", yylineno); }
#line 1901 "parser.c"
    break;

  case 65: /* elist: %empty  */
#line 308 "parser.y"
                  { printf("empty elist : %d\n", yylineno); }
#line 1907 "parser.c"
    break;

  case 66: /* objectdef: SQUARE_BRACKET_OPEN elist SQUARE_BRACKET_CLOSE  */
#line 312 "parser.y"
                                                   { printf("objectdef [ elist ] : %d\n", yylineno); }
#line 1913 "parser.c"
    break;

  case 67: /* objectdef: SQUARE_BRACKET_OPEN indexed SQUARE_BRACKET_CLOSE  */
#line 313 "parser.y"
                                                       { printf("objectdef [ indexed ] : %d\n", yylineno); }
#line 1919 "parser.c"
    break;

  case 68: /* indexed: indexedelem  */
#line 317 "parser.y"
                { printf("indexed indexedelem : %d\n", yylineno); }
#line 1925 "parser.c"
    break;

  case 69: /* indexed: indexed COMMA indexedelem  */
#line 318 "parser.y"
                                { printf("indexed , indexedelem : %d\n", yylineno); }
#line 1931 "parser.c"
    break;

  case 70: /* indexedelem: CURLY_BRACKET_OPEN expr COLON expr CURLY_BRACKET_CLOSE  */
#line 322 "parser.y"
                                                           { printf("indexedelem { expr : expr } : %d\n", yylineno); }
#line 1937 "parser.c"
    break;

  case 71: /* $@4: %empty  */
#line 327 "parser.y"
                       { scope++; printf("scope= %d\n", scope);}
#line 1943 "parser.c"
    break;

  case 72: /* block: CURLY_BRACKET_OPEN $@4 stmts CURLY_BRACKET_CLOSE  */
#line 327 "parser.y"
                                                                                           { hideScope(scope--); }
#line 1949 "parser.c"
    break;

  case 73: /* $@5: %empty  */
#line 331 "parser.y"
                                      {scope++;}
#line 1955 "parser.c"
    break;

  case 74: /* $@6: %empty  */
#line 331 "parser.y"
                                                                      {scope--;}
#line 1961 "parser.c"
    break;

  case 75: /* funcdef: FUNCTION identifiers BRACKET_OPEN $@5 idlist BRACKET_CLOSE $@6 block  */
#line 332 "parser.y"
          {func_counter--; }
#line 1967 "parser.c"
    break;

  case 76: /* identifiers: IDENTIFIER  */
#line 336 "parser.y"
               { printf("IDENTIFIER : %d\n", yylineno);
        Symbol_t* s = SymTable_lookup((yyvsp[0].strVal), scope);
        if(s){
            if(s->type==2){
                printError("Collision with LOCAL_VAR named '%s'",(yyvsp[0].strVal));
            }else{
                printError("Collision with USER_FUNC named '%s'",(yyvsp[0].strVal));
            }
        }else{
            SymTable_insert((yyvsp[0].strVal), USER_FUNC, scope, yylineno);
        }
        func_counter++;
        printf("FUNCTION IDENTIFIER BRACKET_OPEN idlist BRACKET_CLOSE block: %d\n",yylineno);}
#line 1985 "parser.c"
    break;

  case 77: /* identifiers: %empty  */
#line 349 "parser.y"
        { printf("EMPTY IDENTIFIER : %d\n", yylineno);
        char anonymous_funcname[10];
        sprintf(anonymous_funcname, "$%d", anonymous_counter);
        func_counter++;
        SymTable_insert(anonymous_funcname, USER_FUNC, scope, yylineno);
        anonymous_counter++;
        }
#line 1997 "parser.c"
    break;

  case 78: /* const: FLOATCONST  */
#line 359 "parser.y"
               { printf("FLOATCONST : %d\n", yylineno); (yyval.exprVal)=newexpr_constnum((yyvsp[0].floatVal)); }
#line 2003 "parser.c"
    break;

  case 79: /* const: INTCONST  */
#line 360 "parser.y"
               { printf("INTCONST : %d\n", yylineno); (yyval.exprVal)=newexpr_constnum((yyvsp[0].intVal));  }
#line 2009 "parser.c"
    break;

  case 80: /* const: STRING_TOKEN  */
#line 361 "parser.y"
                   { printf("STRING_TOKEN : %d\n", yylineno); (yyval.exprVal)=newexpr_conststring((yyvsp[0].strVal)); }
#line 2015 "parser.c"
    break;

  case 81: /* const: NIL  */
#line 362 "parser.y"
          { printf("NIL : %d\n", yylineno); (yyval.exprVal)=newexpr_nil(); }
#line 2021 "parser.c"
    break;

  case 82: /* const: TRUE  */
#line 363 "parser.y"
           { printf("TRUE : %d\n", yylineno); (yyval.exprVal)=newexpr_constbool(1); }
#line 2027 "parser.c"
    break;

  case 83: /* const: FALSE  */
#line 364 "parser.y"
            { printf("FALSE : %d\n", yylineno); (yyval.exprVal)=newexpr_constnum(0); }
#line 2033 "parser.c"
    break;

  case 84: /* idlist: %empty  */
#line 368 "parser.y"
        {printf("empty idlist: %d\n",yylineno);}
#line 2039 "parser.c"
    break;

  case 85: /* idlist: IDENTIFIER  */
#line 369 "parser.y"
                { 
        if(SymTable_lookupGlobalFuncs((yyvsp[0].strVal))){
            printError("Collision with '%s' library function", (yyvsp[0].strVal));
        }else if(SymTable_lookup((yyvsp[0].strVal), scope)){ 
            printError("Variable '%s' already defined", (yyvsp[0].strVal));
        }else{
            SymTable_insert((yyvsp[0].strVal), FORMAL_ARG, scope, yylineno);
        }
    }
#line 2053 "parser.c"
    break;

  case 86: /* idlist: idlist COMMA IDENTIFIER  */
#line 378 "parser.y"
                              {

        if(SymTable_lookupGlobalFuncs((yyvsp[0].strVal))){
            printError("Collision with '%s' library function", (yyvsp[0].strVal));
        }else if(SymTable_lookup((yyvsp[0].strVal), scope)){ 
            printError("Variable '%s' already defined", (yyvsp[0].strVal));
        }else{
            SymTable_insert((yyvsp[0].strVal), FORMAL_ARG, scope, yylineno);
        }
    }
#line 2068 "parser.c"
    break;

  case 87: /* ifstmt: IF BRACKET_OPEN expr BRACKET_CLOSE stmt  */
#line 392 "parser.y"
        { printf("if ( expr ) stmt : %d\n", yylineno); }
#line 2074 "parser.c"
    break;

  case 88: /* ifstmt: IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt  */
#line 394 "parser.y"
        { printf("if ( expr ) stmt else stmt : %d\n", yylineno); }
#line 2080 "parser.c"
    break;

  case 89: /* $@7: %empty  */
#line 399 "parser.y"
        { loop_counter++; printf("while loop start : %d\n", yylineno); }
#line 2086 "parser.c"
    break;

  case 90: /* whilestmt: WHILE BRACKET_OPEN expr BRACKET_CLOSE $@7 stmt  */
#line 401 "parser.y"
        { loop_counter--; printf("while loop end : %d\n", yylineno); }
#line 2092 "parser.c"
    break;

  case 91: /* $@8: %empty  */
#line 406 "parser.y"
        { loop_counter++; printf("for loop start : %d\n", yylineno); }
#line 2098 "parser.c"
    break;

  case 92: /* forstmt: FOR BRACKET_OPEN elist SEMICOLON expr SEMICOLON elist BRACKET_CLOSE $@8 stmt  */
#line 408 "parser.y"
        { loop_counter--; printf("for loop end : %d\n", yylineno); }
#line 2104 "parser.c"
    break;

  case 93: /* returnstmt: RETURN expr SEMICOLON  */
#line 412 "parser.y"
                          { if (func_counter==0) printError("Use of 'return' while not in a function"); }
#line 2110 "parser.c"
    break;

  case 94: /* returnstmt: RETURN SEMICOLON  */
#line 413 "parser.y"
                       { if (func_counter==0) printError("Use of 'return' while not in a function"); }
#line 2116 "parser.c"
    break;


#line 2120 "parser.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 415 "parser.y"


int yyerror(const char* yaccProvidedMessage){
    fprintf(stderr,"Syntax error at line %d: %s, near '%s'\n",yylineno,yaccProvidedMessage,yytext);
    return 0;
}

void printError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error (line %d): ", yylineno);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    SymTable_init();
    yyparse();
    SymTable_print();
    print_quads();
    write_quads_to_file("quads.txt");
    return 0;
}
