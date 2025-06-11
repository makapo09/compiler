/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     FOR = 261,
     FUNCTION = 262,
     RETURN = 263,
     BREAK = 264,
     CONTINUE = 265,
     AND = 266,
     OR = 267,
     NOT = 268,
     TRUE = 269,
     FALSE = 270,
     NIL = 271,
     LOCAL = 272,
     ASSIGN = 273,
     PLUS = 274,
     MINUS = 275,
     MULTIPLY = 276,
     DIVIDE = 277,
     MODULO = 278,
     EQUAL = 279,
     NOT_EQUAL = 280,
     GREATER_THAN = 281,
     LESS_THAN = 282,
     GREATER_EQUAL = 283,
     LESS_EQUAL = 284,
     INCREMENT = 285,
     DECREMENT = 286,
     BRACKET_OPEN = 287,
     BRACKET_CLOSE = 288,
     CURLY_BRACKET_OPEN = 289,
     CURLY_BRACKET_CLOSE = 290,
     SQUARE_BRACKET_OPEN = 291,
     SQUARE_BRACKET_CLOSE = 292,
     COMMA = 293,
     SEMICOLON = 294,
     COLON = 295,
     DOUBLE_COLON = 296,
     DOT = 297,
     DOUBLE_DOT = 298,
     OTHER = 299,
     IDENTIFIER = 300,
     STRING_TOKEN = 301,
     INTCONST = 302,
     FLOATCONST = 303,
     IFX = 304,
     UMINUS = 305
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define OR 267
#define NOT 268
#define TRUE 269
#define FALSE 270
#define NIL 271
#define LOCAL 272
#define ASSIGN 273
#define PLUS 274
#define MINUS 275
#define MULTIPLY 276
#define DIVIDE 277
#define MODULO 278
#define EQUAL 279
#define NOT_EQUAL 280
#define GREATER_THAN 281
#define LESS_THAN 282
#define GREATER_EQUAL 283
#define LESS_EQUAL 284
#define INCREMENT 285
#define DECREMENT 286
#define BRACKET_OPEN 287
#define BRACKET_CLOSE 288
#define CURLY_BRACKET_OPEN 289
#define CURLY_BRACKET_CLOSE 290
#define SQUARE_BRACKET_OPEN 291
#define SQUARE_BRACKET_CLOSE 292
#define COMMA 293
#define SEMICOLON 294
#define COLON 295
#define DOUBLE_COLON 296
#define DOT 297
#define DOUBLE_DOT 298
#define OTHER 299
#define IDENTIFIER 300
#define STRING_TOKEN 301
#define INTCONST 302
#define FLOATCONST 303
#define IFX 304
#define UMINUS 305




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "icode.h"
#include "bison_symtable.h"
#include "alpha_tokens.h"


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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 30 "parser.y"
{
    char* strVal;
    int intVal;
    float floatVal;
    struct expr* exprVal;
    struct statement* statementVal;
    struct call* callVal;
    struct forprefix forprefixVal;
    unsigned int quadlabel;
}
/* Line 193 of yacc.c.  */
#line 236 "parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 249 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   642

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNRULES -- Number of states.  */
#define YYNSTATES  185

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    15,    17,    20,
      22,    23,    27,    28,    32,    34,    36,    37,    43,    45,
      47,    51,    55,    59,    63,    67,    71,    75,    79,    83,
      87,    91,    95,    99,   101,   105,   108,   111,   114,   117,
     120,   123,   125,   129,   131,   133,   135,   139,   141,   143,
     146,   149,   151,   155,   160,   164,   169,   174,   177,   184,
     186,   188,   192,   198,   200,   204,   205,   209,   213,   215,
     219,   225,   229,   231,   232,   235,   236,   241,   243,   247,
     249,   251,   253,   255,   257,   259,   260,   262,   266,   271,
     274,   279,   281,   285,   286,   287,   297,   305,   309
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    53,    -1,    -1,    53,    54,    -1,    82,
      -1,    83,    84,    54,    -1,    88,    -1,    58,    39,    -1,
      89,    -1,    -1,     9,    39,    55,    -1,    -1,    10,    39,
      56,    -1,    72,    -1,    78,    -1,    -1,    64,    18,    58,
      39,    57,    -1,    39,    -1,    60,    -1,    58,    12,    58,
      -1,    58,    11,    58,    -1,    58,    24,    58,    -1,    58,
      25,    58,    -1,    58,    29,    58,    -1,    58,    27,    58,
      -1,    58,    28,    58,    -1,    58,    26,    58,    -1,    58,
      23,    58,    -1,    58,    22,    58,    -1,    58,    21,    58,
      -1,    58,    20,    58,    -1,    58,    19,    58,    -1,    59,
      -1,    32,    58,    33,    -1,    20,    58,    -1,    13,    58,
      -1,    30,    62,    -1,    62,    30,    -1,    31,    62,    -1,
      62,    31,    -1,    61,    -1,    62,    18,    58,    -1,    62,
      -1,    64,    -1,    69,    -1,    32,    78,    33,    -1,    79,
      -1,    45,    -1,    17,    45,    -1,    41,    45,    -1,    63,
      -1,    62,    42,    45,    -1,    62,    36,    58,    37,    -1,
      64,    42,    45,    -1,    64,    36,    58,    37,    -1,    64,
      32,    68,    33,    -1,    62,    65,    -1,    32,    78,    33,
      32,    68,    33,    -1,    66,    -1,    67,    -1,    32,    68,
      33,    -1,    43,    45,    32,    68,    33,    -1,    58,    -1,
      58,    38,    68,    -1,    -1,    36,    68,    37,    -1,    36,
      70,    37,    -1,    71,    -1,    71,    38,    70,    -1,    34,
      58,    40,    58,    35,    -1,    34,    53,    35,    -1,    45,
      -1,    -1,     7,    73,    -1,    -1,    32,    76,    80,    33,
      -1,    72,    -1,    74,    75,    77,    -1,    48,    -1,    47,
      -1,    46,    -1,    16,    -1,    14,    -1,    15,    -1,    -1,
      45,    -1,    80,    38,    45,    -1,     3,    32,    58,    33,
      -1,    81,    54,    -1,    81,    54,     4,    54,    -1,     5,
      -1,    32,    58,    33,    -1,    -1,    -1,     6,    32,    68,
      39,    86,    58,    39,    68,    33,    -1,    87,    85,    68,
      33,    85,    54,    85,    -1,     8,    58,    39,    -1,     8,
      39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    76,    76,    79,    82,    91,    92,   101,   103,   104,
     105,   105,   106,   106,   107,   108,   109,   109,   110,   116,
     121,   126,   131,   141,   151,   161,   171,   181,   191,   197,
     203,   209,   215,   221,   228,   229,   236,   242,   255,   269,
     282,   296,   300,   318,   319,   320,   321,   325,   329,   348,
     359,   367,   371,   372,   378,   379,   383,   386,   396,   405,
     406,   410,   419,   428,   432,   437,   443,   453,   465,   469,
     476,   484,   489,   505,   516,   523,   523,   526,   529,   536,
     537,   538,   539,   540,   541,   545,   546,   555,   567,   576,
     581,   593,   600,   607,   608,   612,   623,   635,   638
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "OR", "NOT", "TRUE", "FALSE",
  "NIL", "LOCAL", "ASSIGN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "MODULO", "EQUAL", "NOT_EQUAL", "GREATER_THAN", "LESS_THAN",
  "GREATER_EQUAL", "LESS_EQUAL", "INCREMENT", "DECREMENT", "BRACKET_OPEN",
  "BRACKET_CLOSE", "CURLY_BRACKET_OPEN", "CURLY_BRACKET_CLOSE",
  "SQUARE_BRACKET_OPEN", "SQUARE_BRACKET_CLOSE", "COMMA", "SEMICOLON",
  "COLON", "DOUBLE_COLON", "DOT", "DOUBLE_DOT", "OTHER", "IDENTIFIER",
  "STRING_TOKEN", "INTCONST", "FLOATCONST", "IFX", "UMINUS", "$accept",
  "program", "stmts", "stmt", "@1", "@2", "@3", "expr", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "objectdef", "indexed", "indexedelem",
  "block", "funcname", "funcprefix", "funcargs", "@4", "funcbody",
  "funcdef", "const", "idlist", "ifprefix", "ifstmt", "whilestart",
  "whilecond", "N", "M", "forprefix", "forstmt", "returnstmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      55,    54,    56,    54,    54,    54,    57,    54,    54,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    61,    61,    61,    61,    61,    62,    62,
      62,    62,    63,    63,    63,    63,    64,    64,    64,    65,
      65,    66,    67,    68,    68,    68,    69,    69,    70,    70,
      71,    72,    73,    73,    74,    76,    75,    77,    78,    79,
      79,    79,    79,    79,    79,    80,    80,    80,    81,    82,
      82,    83,    84,    85,    86,    87,    88,    89,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     3,     1,     2,     1,
       0,     3,     0,     3,     1,     1,     0,     5,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     2,     2,     2,     2,     2,
       2,     1,     3,     1,     1,     1,     3,     1,     1,     2,
       2,     1,     3,     4,     3,     4,     4,     2,     6,     1,
       1,     3,     5,     1,     3,     0,     3,     3,     1,     3,
       5,     3,     1,     0,     2,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     0,     1,     3,     4,     2,
       4,     1,     3,     0,     0,     9,     7,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,    91,     0,    73,     0,     0,
       0,     0,    83,    84,    82,     0,     0,     0,     0,     0,
       3,    65,    18,     0,    48,    81,    80,    79,     4,     0,
      33,    19,    41,    43,    51,    44,    45,    14,     0,    15,
      47,     0,     5,     0,    93,     7,     9,     0,    65,    72,
      74,    98,     0,    44,    10,    12,    36,    49,    35,     0,
      37,     0,    39,     0,     0,     0,     0,    63,     0,     0,
      68,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,    38,    40,    65,
       0,     0,     0,    57,    59,    60,     0,    65,     0,     0,
      75,     0,    89,     0,     0,    65,     0,     0,    97,    11,
      13,     0,    34,    46,    71,     0,    65,    66,    67,     0,
      21,    20,    32,    31,    30,    29,    28,    22,    23,    27,
      25,    26,    24,    42,     0,     0,    52,     0,     0,     0,
       0,    54,    85,    77,    78,     0,     0,     6,     0,    88,
      94,     0,    65,     0,    64,    69,    61,    53,    65,    16,
      56,    55,    86,     0,    90,    92,    93,     0,     0,     0,
       0,    17,    76,     0,     0,     0,    58,    70,    62,    87,
      93,    65,    96,     0,    95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,   109,   110,   171,    67,    30,    31,
      32,    33,    34,    53,    93,    94,    95,    68,    36,    69,
      70,    37,    50,    38,   101,   142,   144,    39,    40,   163,
      41,    42,    43,   104,   105,   167,    44,    45,    46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -160
static const yytype_int16 yypact[] =
{
    -160,     8,   217,  -160,   -12,  -160,     5,   -41,   289,   -17,
      -1,   333,  -160,  -160,  -160,    -5,   333,    17,    17,   253,
    -160,   325,  -160,     3,  -160,  -160,  -160,  -160,  -160,   100,
    -160,  -160,  -160,    25,  -160,    51,  -160,  -160,    14,  -160,
    -160,   217,  -160,    15,  -160,  -160,  -160,   333,   333,  -160,
    -160,  -160,   364,    53,  -160,  -160,  -160,  -160,  -160,    44,
      72,    53,    72,   504,    19,   171,   333,   427,    16,    22,
      48,  -160,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,  -160,   333,  -160,  -160,   333,
     333,     9,    45,  -160,  -160,  -160,   333,   333,   333,    47,
    -160,    26,    93,   333,   217,   333,   523,    59,  -160,  -160,
    -160,    67,  -160,    71,  -160,     4,   333,  -160,  -160,    75,
     591,   580,   -10,   -10,  -160,  -160,  -160,   602,   602,   613,
     613,   613,   613,   561,    77,   447,  -160,    81,   385,    83,
     466,  -160,    85,  -160,  -160,   217,   542,  -160,    84,  -160,
    -160,    71,   333,   333,  -160,  -160,  -160,  -160,   333,  -160,
    -160,  -160,  -160,   -28,  -160,  -160,  -160,   333,    98,   485,
      99,  -160,  -160,    88,   217,   406,  -160,  -160,  -160,  -160,
    -160,   333,  -160,   101,  -160
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -160,  -160,   116,   -39,  -160,  -160,  -160,    -2,  -160,  -160,
    -160,    18,  -160,     1,  -160,  -160,  -160,     2,  -160,    21,
    -160,    36,  -160,  -160,  -160,  -160,  -160,   -18,  -160,  -160,
    -160,  -160,  -160,  -160,  -159,  -160,  -160,  -160,  -160
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      29,    64,   102,    35,    49,   172,    52,   174,     3,    56,
     173,    76,    77,    78,    58,    72,    73,    63,    61,    61,
      47,   182,    54,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    15,    60,    62,    48,    55,    29,
      57,   111,    35,    86,   153,   106,   100,   103,    71,    59,
     107,     7,   113,   117,   136,    87,    88,    89,    23,   118,
      20,    90,    24,    29,   115,   147,    35,    91,    92,    96,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,    97,   133,    97,   119,    98,   135,    98,
     137,   134,   141,    99,   138,    99,   140,   145,   150,   139,
     151,   146,    29,   152,    89,    35,   164,   148,    90,    66,
     156,    72,    73,   158,    91,    92,   160,   166,   154,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     162,   176,   178,   179,   184,   180,    65,   143,     0,    85,
     155,     0,     0,    29,     0,     0,    35,     0,     0,     0,
       0,   169,     0,     0,   168,     0,     0,     0,     0,     0,
     170,     0,     0,     0,     0,   175,     0,     0,     0,     0,
       0,     0,    29,     0,     4,    35,     5,     6,     7,     8,
       9,    10,     0,   183,    11,    12,    13,    14,    15,     0,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    18,    19,     0,    20,   114,    21,     0,     0,
      22,     0,    23,     0,     0,     0,    24,    25,    26,    27,
       4,     0,     5,     6,     7,     8,     9,    10,     0,     0,
      11,    12,    13,    14,    15,     0,     0,    16,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    18,    19,
       0,    20,     0,    21,     0,     0,    22,     0,    23,     0,
       7,     0,    24,    25,    26,    27,    11,    12,    13,    14,
      15,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,    18,    19,     0,     0,     0,    21,
       0,     0,     0,     0,    23,     0,     0,     0,    24,    25,
      26,    27,    11,    12,    13,    14,    15,     0,     0,    16,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      18,    19,     0,     0,     0,    21,     0,     0,    51,     0,
      23,     0,     0,     0,    24,    25,    26,    27,    11,    12,
      13,    14,    15,     0,     0,    16,    11,    12,    13,    14,
      15,     0,     0,    16,     0,    17,    18,    19,     0,    66,
       0,    21,     0,    17,    18,    19,    23,     0,     0,    21,
      24,    25,    26,    27,    23,    72,    73,     0,    24,    25,
      26,    27,     0,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,     0,     0,    72,    73,     0,     0,
       0,     0,     0,   108,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,     0,     0,    72,    73,     0,
       0,     0,     0,     0,   159,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,     0,    72,    73,
       0,     0,     0,     0,     0,   181,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,     0,    72,    73,
       0,     0,     0,     0,     0,   116,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    72,    73,     0,
       0,     0,     0,     0,   157,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    72,    73,     0,     0,
       0,     0,     0,   161,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    72,    73,     0,     0,     0,
     177,     0,     0,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    72,    73,     0,   112,     0,     0,
       0,     0,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    72,    73,     0,   149,     0,     0,     0,
       0,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    72,    73,     0,   165,     0,     0,     0,     0,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    72,     0,     0,     0,     0,     0,     0,     0,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    74,    75,    76,    77,    78,    -1,    -1,    81,    82,
      83,    84,    74,    75,    76,    77,    78,     0,     0,    -1,
      -1,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
       2,    19,    41,     2,    45,    33,     8,   166,     0,    11,
      38,    21,    22,    23,    16,    11,    12,    19,    17,    18,
      32,   180,    39,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    17,    17,    18,    32,    39,    41,
      45,    59,    41,    18,    40,    47,    32,    32,    45,    32,
      48,     7,    33,    37,    45,    30,    31,    32,    41,    37,
      34,    36,    45,    65,    66,   104,    65,    42,    43,    18,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    32,    86,    32,    38,    36,    90,    36,
      45,    89,    45,    42,    96,    42,    98,     4,    39,    97,
      33,   103,   104,    32,    32,   104,   145,   105,    36,    34,
      33,    11,    12,    32,    42,    43,    33,    33,   116,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      45,    33,    33,    45,    33,   174,    20,   101,    -1,    39,
     119,    -1,    -1,   145,    -1,    -1,   145,    -1,    -1,    -1,
      -1,   153,    -1,    -1,   152,    -1,    -1,    -1,    -1,    -1,
     158,    -1,    -1,    -1,    -1,   167,    -1,    -1,    -1,    -1,
      -1,    -1,   174,    -1,     3,   174,     5,     6,     7,     8,
       9,    10,    -1,   181,    13,    14,    15,    16,    17,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    -1,    34,    35,    36,    -1,    -1,
      39,    -1,    41,    -1,    -1,    -1,    45,    46,    47,    48,
       3,    -1,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      -1,    34,    -1,    36,    -1,    -1,    39,    -1,    41,    -1,
       7,    -1,    45,    46,    47,    48,    13,    14,    15,    16,
      17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    46,
      47,    48,    13,    14,    15,    16,    17,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    -1,    -1,    -1,    36,    -1,    -1,    39,    -1,
      41,    -1,    -1,    -1,    45,    46,    47,    48,    13,    14,
      15,    16,    17,    -1,    -1,    20,    13,    14,    15,    16,
      17,    -1,    -1,    20,    -1,    30,    31,    32,    -1,    34,
      -1,    36,    -1,    30,    31,    32,    41,    -1,    -1,    36,
      45,    46,    47,    48,    41,    11,    12,    -1,    45,    46,
      47,    48,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    39,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    11,    12,    -1,
      -1,    -1,    -1,    -1,    39,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    39,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    38,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    11,    12,    -1,
      -1,    -1,    -1,    -1,    37,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    11,    12,    -1,    -1,
      -1,    -1,    -1,    37,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    11,    12,    -1,    -1,    -1,
      35,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    11,    12,    -1,    33,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    11,    12,    -1,    33,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    11,    12,    -1,    33,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    19,    20,    21,    22,    23,    -1,    -1,    26,
      27,    28,    29
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    53,     0,     3,     5,     6,     7,     8,     9,
      10,    13,    14,    15,    16,    17,    20,    30,    31,    32,
      34,    36,    39,    41,    45,    46,    47,    48,    54,    58,
      59,    60,    61,    62,    63,    64,    69,    72,    74,    78,
      79,    81,    82,    83,    87,    88,    89,    32,    32,    45,
      73,    39,    58,    64,    39,    39,    58,    45,    58,    32,
      62,    64,    62,    58,    78,    53,    34,    58,    68,    70,
      71,    45,    11,    12,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    39,    18,    30,    31,    32,
      36,    42,    43,    65,    66,    67,    18,    32,    36,    42,
      32,    75,    54,    32,    84,    85,    58,    68,    39,    55,
      56,    78,    33,    33,    35,    58,    38,    37,    37,    38,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    68,    58,    45,    45,    58,    68,
      58,    45,    76,    72,    77,     4,    58,    54,    68,    33,
      39,    33,    32,    40,    68,    70,    33,    37,    32,    39,
      33,    37,    45,    80,    54,    33,    33,    86,    68,    58,
      68,    57,    33,    38,    85,    58,    33,    35,    33,    45,
      54,    39,    85,    68,    33
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 76 "parser.y"
    {printf("program starting here: %d\n",yylineno);}
    break;

  case 3:
#line 79 "parser.y"
    {
        (yyval.statementVal) = create_statement();
    }
    break;

  case 4:
#line 82 "parser.y"
    {
        (yyval.statementVal) = create_statement();
        (yyval.statementVal)->breaklist = mergelist((yyvsp[(1) - (2)].statementVal)->breaklist, (yyvsp[(2) - (2)].statementVal)->breaklist);
        (yyval.statementVal)->contlist  = mergelist((yyvsp[(1) - (2)].statementVal)->contlist, (yyvsp[(2) - (2)].statementVal)->contlist);
    }
    break;

  case 5:
#line 91 "parser.y"
    {printf("ifstmt: %d\n",yylineno); (yyval.statementVal)=(yyvsp[(1) - (1)].statementVal);}
    break;

  case 6:
#line 92 "parser.y"
    {
    emit(jump, NULL, NULL, NULL, (yyvsp[(1) - (3)].quadlabel), yylineno);              
    patchlabel((yyvsp[(2) - (3)].quadlabel), nextquadlabel());                        
    if ((yyvsp[(3) - (3)].statementVal)) {
    patchlist((yyvsp[(3) - (3)].statementVal)->breaklist, nextquadlabel());
    patchlist((yyvsp[(3) - (3)].statementVal)->contlist, (yyvsp[(1) - (3)].quadlabel));
    }                  
    (yyval.statementVal) = create_statement();
    }
    break;

  case 7:
#line 102 "parser.y"
    { (yyval.statementVal) = (yyvsp[(1) - (1)].statementVal); }
    break;

  case 8:
#line 103 "parser.y"
    {printf("expr SEMICOLON: %d\n",yylineno); (yyval.statementVal)=create_statement();}
    break;

  case 9:
#line 104 "parser.y"
    {printf("returnstmt: %d\n",yylineno); (yyval.statementVal)=(yyvsp[(1) - (1)].statementVal);}
    break;

  case 10:
#line 105 "parser.y"
    { if (loop_counter==0) printError("Use of 'break' while not in a loop"); }
    break;

  case 11:
#line 105 "parser.y"
    {printf("break semicolon : %d\n",yylineno); (yyval.statementVal)=create_statement();}
    break;

  case 12:
#line 106 "parser.y"
    { if (loop_counter==0) printError("Use of 'continue' while not in a loop"); }
    break;

  case 13:
#line 106 "parser.y"
    {printf("continue semicolon : %d\n",yylineno); (yyval.statementVal)=create_statement();}
    break;

  case 14:
#line 107 "parser.y"
    {printf("block : %d\n",yylineno); (yyval.statementVal)=(yyvsp[(1) - (1)].statementVal);}
    break;

  case 15:
#line 108 "parser.y"
    {printf("funcdef : %d\n",yylineno); (yyval.statementVal)=create_statement();}
    break;

  case 16:
#line 109 "parser.y"
    { printError("Grammar error: Function call is not lvalue"); }
    break;

  case 17:
#line 109 "parser.y"
    {printf("call assign expr semicolon : %d\n",yylineno);}
    break;

  case 18:
#line 110 "parser.y"
    {printf("semicolon : %d\n",yylineno); (yyval.statementVal)=create_statement();}
    break;

  case 19:
#line 116 "parser.y"
    {
        is_not_member = 1;
        (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);
        printf("assignexpr: %d\n", yylineno);
    }
    break;

  case 20:
#line 121 "parser.y"
    {
            (yyval.exprVal) = newtemp();
            (yyval.exprVal)->type = boolexpr_e;
            emit(or, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), (yyval.exprVal), 0, yylineno);
        }
    break;

  case 21:
#line 126 "parser.y"
    {
            (yyval.exprVal) = newtemp();
            (yyval.exprVal)->type = boolexpr_e;
            emit(and, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), (yyval.exprVal), 0, yylineno);
        }
    break;

  case 22:
#line 131 "parser.y"
    {
                printf("expr equal expr : %d\n", yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = boolexpr_e;

                emit(if_eq, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, (yyval.exprVal), 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, (yyval.exprVal), 0, yylineno);
        }
    break;

  case 23:
#line 141 "parser.y"
    {
                printf("expr not_equal expr : %d\n", yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = boolexpr_e;

                emit(if_noteq, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, (yyval.exprVal), 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, (yyval.exprVal), 0, yylineno);
        }
    break;

  case 24:
#line 151 "parser.y"
    {
                printf("expr less_equal expr : %d\n", yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = boolexpr_e;

                emit(if_lesseq, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, (yyval.exprVal), 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, (yyval.exprVal), 0, yylineno);
        }
    break;

  case 25:
#line 161 "parser.y"
    {
                printf("expr less_than expr : %d\n", yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = boolexpr_e;

                emit(if_less, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, (yyval.exprVal), 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, (yyval.exprVal), 0, yylineno);
        }
    break;

  case 26:
#line 171 "parser.y"
    {
                printf("expr greater_equal expr : %d\n", yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = boolexpr_e;

                emit(if_greatereq, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, (yyval.exprVal), 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, (yyval.exprVal), 0, yylineno);
        }
    break;

  case 27:
#line 181 "parser.y"
    {
                printf("expr greater_than expr : %d\n", yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = boolexpr_e;

                emit(if_greater, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, (yyval.exprVal), 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, (yyval.exprVal), 0, yylineno);
        }
    break;

  case 28:
#line 191 "parser.y"
    {
        printf("expr modulo expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(mod, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), (yyval.exprVal), 0, yylineno);
    }
    break;

  case 29:
#line 197 "parser.y"
    {
        printf("expr divide expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(div_i, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), (yyval.exprVal), 0, yylineno);
    }
    break;

  case 30:
#line 203 "parser.y"
    {
        printf("expr multiply expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(mul, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), (yyval.exprVal), 0, yylineno);
    }
    break;

  case 31:
#line 209 "parser.y"
    {
        printf("expr minus expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(sub, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), (yyval.exprVal), 0, yylineno);
    }
    break;

  case 32:
#line 215 "parser.y"
    {
        printf("expr plus expr : %d\n", yylineno);
        (yyval.exprVal) = newexpr(arithexpr_e);
        (yyval.exprVal)->sym = newtemp()->sym;
        emit(add, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), (yyval.exprVal), 0, yylineno);
    }
    break;

  case 33:
#line 221 "parser.y"
    {
        (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);
        printf("term : %d\n", yylineno);
    }
    break;

  case 34:
#line 228 "parser.y"
    { printf("bracket_open expr bracket_close : %d\n", yylineno); (yyval.exprVal) = (yyvsp[(2) - (3)].exprVal);}
    break;

  case 35:
#line 229 "parser.y"
    { 
        printf("minus expr : %d\n", yylineno); 
        check_arith((yyvsp[(2) - (2)].exprVal));
        (yyval.exprVal) = newtemp();
        (yyval.exprVal)->type = arithexpr_e;
        emit(uminus, (yyvsp[(2) - (2)].exprVal), NULL, (yyval.exprVal), 0, yylineno);
    }
    break;

  case 36:
#line 236 "parser.y"
    {
        (yyval.exprVal) = newtemp();
        (yyval.exprVal)->type = boolexpr_e;
        emit(not, (yyvsp[(2) - (2)].exprVal), NULL, (yyval.exprVal), 0, yylineno);
        printf("not expr : %d\n", yylineno);
    }
    break;

  case 37:
#line 242 "parser.y"
    { printf("increment lvalue : %d\n", yylineno); 
            check_arith((yyvsp[(2) - (2)].exprVal));
            if((yyvsp[(2) - (2)].exprVal)->type == tableitem_e) {
                (yyval.exprVal) = emit_iftableitem((yyvsp[(2) - (2)].exprVal));
                emit(add, (yyval.exprVal), newexpr_constnum(1), (yyval.exprVal), 0, yylineno);
                emit(tablesetelem, (yyvsp[(2) - (2)].exprVal)->index, (yyval.exprVal), (yyvsp[(2) - (2)].exprVal), 0, yylineno);
            } else {
                emit(add, (yyvsp[(2) - (2)].exprVal), newexpr_constnum(1), (yyvsp[(2) - (2)].exprVal), 0, yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = arithexpr_e;
                emit(assign, (yyvsp[(2) - (2)].exprVal), NULL, (yyval.exprVal), 0, yylineno);
            }
    }
    break;

  case 38:
#line 255 "parser.y"
    { printf("lvalue increment : %d\n", yylineno); 
            check_arith((yyvsp[(1) - (2)].exprVal));
            (yyval.exprVal) = newtemp();
            (yyval.exprVal)->type = var_e;
            if((yyvsp[(1) - (2)].exprVal)->type == tableitem_e) {
                expr* val = emit_iftableitem((yyvsp[(1) - (2)].exprVal));
                emit(assign, val, NULL, (yyval.exprVal), 0, yylineno);
                emit(add, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, (yyvsp[(1) - (2)].exprVal)->index, val, (yyvsp[(1) - (2)].exprVal), 0, yylineno);
            } else {
                emit(assign, (yyvsp[(1) - (2)].exprVal), NULL, (yyval.exprVal), 0, yylineno);
                emit(add, (yyvsp[(1) - (2)].exprVal), newexpr_constnum(1), (yyvsp[(1) - (2)].exprVal), 0, yylineno);
            }
    }
    break;

  case 39:
#line 269 "parser.y"
    { printf("decrement lvalue : %d\n", yylineno);
            check_arith((yyvsp[(2) - (2)].exprVal));
            if((yyvsp[(2) - (2)].exprVal)->type == tableitem_e) {
                (yyval.exprVal) = emit_iftableitem((yyvsp[(2) - (2)].exprVal));
                emit(sub, (yyval.exprVal), newexpr_constnum(1), (yyval.exprVal), 0, yylineno);
                emit(tablesetelem, (yyvsp[(2) - (2)].exprVal)->index, (yyval.exprVal), (yyvsp[(2) - (2)].exprVal), 0, yylineno);
            } else {
                emit(sub, (yyvsp[(2) - (2)].exprVal), newexpr_constnum(1), (yyvsp[(2) - (2)].exprVal), 0, yylineno);
                (yyval.exprVal) = newtemp();
                (yyval.exprVal)->type = arithexpr_e;
                emit(assign, (yyvsp[(2) - (2)].exprVal), NULL, (yyval.exprVal), 0, yylineno);
            }
    }
    break;

  case 40:
#line 282 "parser.y"
    { printf("lvalue decrement : %d\n", yylineno);
            check_arith((yyvsp[(1) - (2)].exprVal));
            (yyval.exprVal) = newtemp();
            (yyval.exprVal)->type = var_e;
            if((yyvsp[(1) - (2)].exprVal)->type == tableitem_e) {
                expr* val = emit_iftableitem((yyvsp[(1) - (2)].exprVal));
                emit(assign, val, NULL, (yyval.exprVal), 0, yylineno);
                emit(sub, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, (yyvsp[(1) - (2)].exprVal)->index, val, (yyvsp[(1) - (2)].exprVal), 0, yylineno);
            } else {
                emit(assign, (yyvsp[(1) - (2)].exprVal), NULL, (yyval.exprVal), 0, yylineno);
                emit(sub, (yyvsp[(1) - (2)].exprVal), newexpr_constnum(1), (yyvsp[(1) - (2)].exprVal), 0, yylineno);
            }
    }
    break;

  case 41:
#line 296 "parser.y"
    { printf("primary : %d\n", yylineno);  (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);}
    break;

  case 42:
#line 300 "parser.y"
    {
        printf("lvalue ASSIGN expr %d\n", yylineno);
        Symbol_t* s = SymTable_lookup((yyvsp[(1) - (3)].exprVal)->sym->name, scope);
        if(s && (s->type==USER_FUNC || s->type==LIB_FUNC) && is_not_member)
            printError("Using %s '%s' as an lvalue", (s->type==LIB_FUNC)?"LibFunc":"ProgramFunc", (yyvsp[(1) - (3)].exprVal));

        if((yyvsp[(1) - (3)].exprVal)->type == tableitem_e) {
            emit(tablesetelem, (yyvsp[(1) - (3)].exprVal)->index, (yyvsp[(3) - (3)].exprVal), (yyvsp[(1) - (3)].exprVal), 0, yylineno);
            (yyval.exprVal) = emit_iftableitem((yyvsp[(1) - (3)].exprVal));
            (yyval.exprVal)->type = assignexpr_e;
        } else {
            emit(assign, (yyvsp[(3) - (3)].exprVal), NULL, (yyvsp[(1) - (3)].exprVal), 0, yylineno);
            (yyval.exprVal) = newtemp();
            emit(assign, (yyvsp[(1) - (3)].exprVal), NULL, (yyval.exprVal), 0, yylineno);
        }
    }
    break;

  case 43:
#line 318 "parser.y"
    {printf("lvalue : %d\n",yylineno); (yyval.exprVal) = emit_iftableitem((yyvsp[(1) - (1)].exprVal));}
    break;

  case 44:
#line 319 "parser.y"
    {printf("call : %d\n",yylineno);}
    break;

  case 45:
#line 320 "parser.y"
    {printf("objectdef : %d\n",yylineno);}
    break;

  case 46:
#line 321 "parser.y"
    { (yyval.exprVal) = NULL;  printf("bracket_open funcdef bracket_close : %d\n",yylineno);
        (yyval.exprVal) = newexpr(programfunc_e);
        (yyval.exprVal)->sym = (yyvsp[(2) - (3)].exprVal)->sym;
    }
    break;

  case 47:
#line 325 "parser.y"
    {printf("const : %d\n",yylineno); (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);}
    break;

  case 48:
#line 329 "parser.y"
    {
        Symbol_t* s;
        int temp_scope = scope;
        while(temp_scope >= 0){
            s = SymTable_lookup((yyvsp[(1) - (1)].strVal),temp_scope);
            if(s) break;
            temp_scope--;
        }
        if(s && (s->type==USER_FUNC || s->type==LIB_FUNC) && is_not_member){
            printError("Using %s '%s' as an lvalue", (s->type==LIB_FUNC)?"LibFunc":"ProgramFunc", (yyvsp[(1) - (1)].strVal));
        }else if (s && s->type != LIB_FUNC && s->scope != 0 && s->scope < scope && s->scope < func_counter){
            printError("Cannot access '%s' identifier that is located before function", (yyvsp[(1) - (1)].strVal));
        }else if(!s){
            SymTable_insert((yyvsp[(1) - (1)].strVal), (scope==0)?GLOBAL_VAR:LOCAL_VAR, scope, yylineno);}
        
        (yyval.exprVal) = newexpr(var_e);
        (yyval.exprVal)->sym = SymTable_lookup((yyvsp[(1) - (1)].strVal),scope);
        printf("identifier : %d\n",yylineno);
    }
    break;

  case 49:
#line 348 "parser.y"
    {
        if(SymTable_lookupGlobal((yyvsp[(2) - (2)].strVal)) && SymTable_lookupGlobal((yyvsp[(2) - (2)].strVal))->type == LIB_FUNC)
            printError("Collision with '%s' library function", (yyvsp[(2) - (2)].strVal));
        else if(!SymTable_lookup((yyvsp[(2) - (2)].strVal), scope)) {
            SymTable_insert((yyvsp[(2) - (2)].strVal), (scope==0)?GLOBAL_VAR:LOCAL_VAR, scope, yylineno); 
        }
        
        (yyval.exprVal) = newexpr(var_e);
        (yyval.exprVal)->sym = SymTable_lookup((yyvsp[(2) - (2)].strVal), scope);
        printf("local identifier : %d\n",yylineno);
    }
    break;

  case 50:
#line 359 "parser.y"
    {
        if(!SymTable_lookupGlobal((yyvsp[(2) - (2)].strVal)))
            printError("No global variable '::%s' exists", (yyvsp[(2) - (2)].strVal));
        
        (yyval.exprVal) = newexpr(var_e);
        (yyval.exprVal)->sym = SymTable_lookupGlobal((yyvsp[(2) - (2)].strVal));
        printf("double_colon identifier : %d\n",yylineno);
    }
    break;

  case 51:
#line 367 "parser.y"
    { (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal); printf("member : %d\n",yylineno);}
    break;

  case 52:
#line 371 "parser.y"
    { printf("lvalue DOT IDENTIFIER : %d\n", yylineno); (yyval.exprVal) = member_item((yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].strVal)); }
    break;

  case 53:
#line 372 "parser.y"
    { printf("lvalue [ expr ] : %d\n", yylineno);
            (yyvsp[(1) - (4)].exprVal) = emit_iftableitem((yyvsp[(1) - (4)].exprVal));
            (yyval.exprVal) = newexpr(tableitem_e);
            (yyval.exprVal)->sym = (yyvsp[(1) - (4)].exprVal)->sym;
            (yyval.exprVal)->index = (yyvsp[(3) - (4)].exprVal);
    }
    break;

  case 54:
#line 378 "parser.y"
    {is_not_member = 0; printf("call DOT IDENTIFIER : %d\n", yylineno); (yyval.exprVal) = (yyvsp[(1) - (3)].exprVal); }
    break;

  case 55:
#line 379 "parser.y"
    { printf("call [ expr ] : %d\n", yylineno); (yyval.exprVal) = (yyvsp[(1) - (4)].exprVal);}
    break;

  case 56:
#line 383 "parser.y"
    { printf("call ( elist ) : %d\n", yylineno); 
        (yyval.exprVal) = make_call((yyvsp[(1) - (4)].exprVal), (yyvsp[(3) - (4)].exprVal));
    }
    break;

  case 57:
#line 386 "parser.y"
    { printf("lvalue callsuffix : %d\n", yylineno); 
        (yyvsp[(1) - (2)].exprVal) = emit_iftableitem((yyvsp[(1) - (2)].exprVal));
        if((yyvsp[(2) - (2)].callVal)->isMethod){
            expr* t = (yyvsp[(1) - (2)].exprVal);
            (yyvsp[(1) - (2)].exprVal) = emit_iftableitem(member_item(t, (yyvsp[(2) - (2)].callVal)->name));
            (yyvsp[(2) - (2)].callVal)->elist->next = t;
        }

        (yyval.exprVal) = make_call((yyvsp[(1) - (2)].exprVal), (yyvsp[(2) - (2)].callVal)->elist);
    }
    break;

  case 58:
#line 396 "parser.y"
    { printf("( funcdef )( elist ) : %d\n", yylineno); 
        expr* func = newexpr(programfunc_e);
        func->sym = (yyvsp[(2) - (6)].exprVal)->sym;
        (yyval.exprVal) = make_call(func, (yyvsp[(5) - (6)].exprVal));
    }
    break;

  case 59:
#line 405 "parser.y"
    { printf("normcall : %d\n", yylineno); (yyval.callVal) = (yyvsp[(1) - (1)].callVal);}
    break;

  case 60:
#line 406 "parser.y"
    { printf("methodcall : %d\n", yylineno);  (yyval.callVal) = (yyvsp[(1) - (1)].callVal); }
    break;

  case 61:
#line 410 "parser.y"
    { printf("normcall ( elist ) : %d\n", yylineno);
        (yyval.callVal) = malloc(sizeof(struct call));
        (yyval.callVal)->elist = (yyvsp[(2) - (3)].exprVal);
        (yyval.callVal)->isMethod = 0;
        (yyval.callVal)->name = NULL;
    }
    break;

  case 62:
#line 419 "parser.y"
    { printf("methodcall ..IDENTIFIER( elist ) : %d\n", yylineno); 
        (yyval.callVal) = malloc(sizeof(struct call));
        (yyval.callVal)->elist = (yyvsp[(4) - (5)].exprVal);
        (yyval.callVal)->isMethod = 1;
        (yyval.callVal)->name = strdup((yyvsp[(2) - (5)].strVal));
    }
    break;

  case 63:
#line 428 "parser.y"
    { printf("elist expr : %d\n", yylineno); 
        (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);
        (yyval.exprVal)->next = NULL;
    }
    break;

  case 64:
#line 432 "parser.y"
    { printf("elist , expr : %d\n", yylineno); 
        (yyvsp[(1) - (3)].exprVal)->next = (yyvsp[(3) - (3)].exprVal);
        (yyval.exprVal) = (yyvsp[(1) - (3)].exprVal);

    }
    break;

  case 65:
#line 437 "parser.y"
    { printf("empty elist : %d\n", yylineno);
        (yyval.exprVal) = NULL;
    }
    break;

  case 66:
#line 443 "parser.y"
    { printf("objectdef [ elist ] : %d\n", yylineno); 
        expr* t = newtemp();
        t->type = newtable_e;
        emit(tablecreate, NULL, NULL, t, 0, yylineno);
        int i = 0;
        for(expr* tmp = (yyvsp[(2) - (3)].exprVal); tmp; tmp = tmp->next, i++){
            emit(tablesetelem, newexpr_constnum(i), tmp, t, 0, yylineno);
        }
        (yyval.exprVal) = t;
    }
    break;

  case 67:
#line 453 "parser.y"
    { printf("objectdef [ indexed ] : %d\n", yylineno); 
        expr* t = newtemp();
        t->type = newtable_e;
        emit(tablecreate, NULL, NULL, t, 0, yylineno);
        for(expr* tmp = (yyvsp[(2) - (3)].exprVal); tmp; tmp = tmp->next){
            emit(tablesetelem, tmp, tmp->index, t, 0, yylineno);
        }
        (yyval.exprVal) = t;
    }
    break;

  case 68:
#line 465 "parser.y"
    { printf("indexed indexedelem : %d\n", yylineno); 
        (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);
        (yyval.exprVal)->next = NULL;
    }
    break;

  case 69:
#line 469 "parser.y"
    { printf("indexed , indexedelem : %d\n", yylineno); 
        (yyvsp[(1) - (3)].exprVal)->next = (yyvsp[(3) - (3)].exprVal);
        (yyval.exprVal) = (yyvsp[(1) - (3)].exprVal);
    }
    break;

  case 70:
#line 476 "parser.y"
    { printf("indexedelem { expr : expr } : %d\n", yylineno); 
        (yyvsp[(2) - (5)].exprVal)->index = (yyvsp[(4) - (5)].exprVal);
        (yyval.exprVal) = (yyvsp[(2) - (5)].exprVal);
    }
    break;

  case 71:
#line 484 "parser.y"
    { (yyval.statementVal) = (yyvsp[(2) - (3)].statementVal); }
    break;

  case 72:
#line 489 "parser.y"
    {
    
            printf("funcname IDENTIFIER : %d\n", yylineno);

            Symbol_t* s = SymTable_lookup((yyvsp[(1) - (1)].strVal), scope);
            if(s){
                if(s->type==2){
                    printError("Collision with LOCAL_VAR named '%s'",(yyvsp[(1) - (1)].strVal));
                }else{
                    printError("Collision with USER_FUNC named '%s'",(yyvsp[(1) - (1)].strVal));
                }
            }else{
                SymTable_insert((yyvsp[(1) - (1)].strVal), USER_FUNC, scope, yylineno);
            }
            (yyval.strVal) = (yyvsp[(1) - (1)].strVal);
        }
    break;

  case 73:
#line 505 "parser.y"
    {
            printf("empty funcname : %d\n", yylineno);
            char anonymous_funcname[10];
            sprintf(anonymous_funcname, "$%d", anonymous_counter);
            SymTable_insert(anonymous_funcname, USER_FUNC, scope, yylineno);
            anonymous_counter++;

            (yyval.strVal) = strdup(anonymous_funcname);
        }
    break;

  case 74:
#line 516 "parser.y"
    {
                (yyval.exprVal) = newexpr(programfunc_e);
                (yyval.exprVal)->sym = SymTable_lookup((yyvsp[(2) - (2)].strVal), scope);
                emit(funcstart, (yyval.exprVal), NULL, NULL, 0, yylineno);
            }
    break;

  case 75:
#line 523 "parser.y"
    {scope++;}
    break;

  case 76:
#line 523 "parser.y"
    {scope--;}
    break;

  case 77:
#line 526 "parser.y"
    {func_counter--; }
    break;

  case 78:
#line 529 "parser.y"
    {
                (yyval.exprVal) = (yyvsp[(1) - (3)].exprVal);
                emit(funcend, (yyval.exprVal), NULL, NULL, 0, yylineno);
            }
    break;

  case 79:
#line 536 "parser.y"
    { printf("FLOATCONST : %d\n", yylineno); (yyval.exprVal)=newexpr_constnum((yyvsp[(1) - (1)].floatVal)); }
    break;

  case 80:
#line 537 "parser.y"
    { printf("INTCONST : %d\n", yylineno); (yyval.exprVal)=newexpr_constnum((yyvsp[(1) - (1)].intVal));  }
    break;

  case 81:
#line 538 "parser.y"
    { printf("STRING_TOKEN : %d\n", yylineno); (yyval.exprVal)=newexpr_conststring((yyvsp[(1) - (1)].strVal)); }
    break;

  case 82:
#line 539 "parser.y"
    { printf("NIL : %d\n", yylineno); (yyval.exprVal)=newexpr_nil(); }
    break;

  case 83:
#line 540 "parser.y"
    { printf("TRUE : %d\n", yylineno); (yyval.exprVal)=newexpr_constbool(1); }
    break;

  case 84:
#line 541 "parser.y"
    { printf("FALSE : %d\n", yylineno); (yyval.exprVal)=newexpr_constbool(0); }
    break;

  case 85:
#line 545 "parser.y"
    {printf("empty idlist: %d\n",yylineno);}
    break;

  case 86:
#line 546 "parser.y"
    { 
        if(SymTable_lookupGlobalFuncs((yyvsp[(1) - (1)].strVal))){
            printError("Collision with '%s' library function", (yyvsp[(1) - (1)].strVal));
        }else if(SymTable_lookup((yyvsp[(1) - (1)].strVal), scope)){ 
            printError("Variable '%s' already defined", (yyvsp[(1) - (1)].strVal));
        }else{
            SymTable_insert((yyvsp[(1) - (1)].strVal), FORMAL_ARG, scope, yylineno);
        }
    }
    break;

  case 87:
#line 555 "parser.y"
    {

        if(SymTable_lookupGlobalFuncs((yyvsp[(3) - (3)].strVal))){
            printError("Collision with '%s' library function", (yyvsp[(3) - (3)].strVal));
        }else if(SymTable_lookup((yyvsp[(3) - (3)].strVal), scope)){ 
            printError("Variable '%s' already defined", (yyvsp[(3) - (3)].strVal));
        }else{
            SymTable_insert((yyvsp[(3) - (3)].strVal), FORMAL_ARG, scope, yylineno);
        }
    }
    break;

  case 88:
#line 568 "parser.y"
    {
        emit(if_eq, (yyvsp[(3) - (4)].exprVal), newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        (yyval.quadlabel) = nextquadlabel();
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
    break;

  case 89:
#line 577 "parser.y"
    {
        patchlabel((yyvsp[(1) - (2)].quadlabel), nextquadlabel());
        (yyval.statementVal) = (yyvsp[(2) - (2)].statementVal);
    }
    break;

  case 90:
#line 582 "parser.y"
    {
        unsigned after_if = nextquadlabel();
        emit(jump, NULL, NULL, NULL, 0, yylineno);  
        patchlabel((yyvsp[(1) - (4)].quadlabel), nextquadlabel());              
        patchlabel(after_if, nextquadlabel());        
        (yyval.statementVal) = create_statement(); 
    }
    break;

  case 91:
#line 593 "parser.y"
    {
        (yyval.quadlabel) = nextquadlabel();
        ++loop_counter;
    }
    break;

  case 92:
#line 600 "parser.y"
    {
        emit(if_eq, (yyvsp[(2) - (3)].exprVal), newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        (yyval.quadlabel) = nextquadlabel(); 
        emit(jump, NULL, NULL, NULL, 0, yylineno); 
    }
    break;

  case 93:
#line 607 "parser.y"
    { (yyval.quadlabel) = nextquadlabel(); emit(jump, NULL, NULL, NULL, 0, yylineno); }
    break;

  case 94:
#line 608 "parser.y"
    { (yyval.quadlabel) = nextquadlabel(); }
    break;

  case 95:
#line 612 "parser.y"
    {
        (yyval.forprefixVal).test = (yyvsp[(5) - (9)].quadlabel);                 
        expr* cond = make_bool_expr((yyvsp[(6) - (9)].exprVal));  
        emit(if_eq, cond, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);  
        (yyval.forprefixVal).enter = nextquadlabel();
        emit(assign, NULL, NULL, NULL, 0, yylineno); 
    }
    break;

  case 96:
#line 623 "parser.y"
    {
        patchlabel((yyvsp[(1) - (7)].forprefixVal).enter, (yyvsp[(2) - (7)].quadlabel) + 1);      
        patchlabel((yyvsp[(2) - (7)].quadlabel), nextquadlabel());    
        patchlabel((yyvsp[(5) - (7)].quadlabel), (yyvsp[(1) - (7)].forprefixVal).test);           
        patchlabel((yyvsp[(7) - (7)].quadlabel), (yyvsp[(2) - (7)].quadlabel) + 1);              
        patchlist((yyvsp[(6) - (7)].statementVal)->breaklist, nextquadlabel());
        patchlist((yyvsp[(6) - (7)].statementVal)->contlist, (yyvsp[(2) - (7)].quadlabel) + 1);
        (yyval.statementVal) = (yyvsp[(6) - (7)].statementVal);
    }
    break;

  case 97:
#line 635 "parser.y"
    { if (func_counter==0) printError("Use of 'return' while not in a function"); 
        emit(ret, (yyvsp[(2) - (3)].exprVal), NULL, NULL, 0, yylineno);
    }
    break;

  case 98:
#line 638 "parser.y"
    { if (func_counter==0) printError("Use of 'return' while not in a function"); 
        emit(ret, NULL, NULL, NULL, 0, yylineno);
    }
    break;


/* Line 1267 of yacc.c.  */
#line 2564 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 642 "parser.y"


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
    print_quads(stdout);
    write_quads_to_file("quads.txt");
    return 0;
}

