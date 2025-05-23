/* A Bison parser, made by GNU Bison 3.7.5.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    WHILE = 260,                   /* WHILE  */
    FOR = 261,                     /* FOR  */
    FUNCTION = 262,                /* FUNCTION  */
    RETURN = 263,                  /* RETURN  */
    BREAK = 264,                   /* BREAK  */
    CONTINUE = 265,                /* CONTINUE  */
    AND = 266,                     /* AND  */
    OR = 267,                      /* OR  */
    NOT = 268,                     /* NOT  */
    TRUE = 269,                    /* TRUE  */
    FALSE = 270,                   /* FALSE  */
    NIL = 271,                     /* NIL  */
    LOCAL = 272,                   /* LOCAL  */
    ASSIGN = 273,                  /* ASSIGN  */
    PLUS = 274,                    /* PLUS  */
    MINUS = 275,                   /* MINUS  */
    MULTIPLY = 276,                /* MULTIPLY  */
    DIVIDE = 277,                  /* DIVIDE  */
    MODULO = 278,                  /* MODULO  */
    EQUAL = 279,                   /* EQUAL  */
    NOT_EQUAL = 280,               /* NOT_EQUAL  */
    GREATER_THAN = 281,            /* GREATER_THAN  */
    LESS_THAN = 282,               /* LESS_THAN  */
    GREATER_EQUAL = 283,           /* GREATER_EQUAL  */
    LESS_EQUAL = 284,              /* LESS_EQUAL  */
    INCREMENT = 285,               /* INCREMENT  */
    DECREMENT = 286,               /* DECREMENT  */
    BRACKET_OPEN = 287,            /* BRACKET_OPEN  */
    BRACKET_CLOSE = 288,           /* BRACKET_CLOSE  */
    CURLY_BRACKET_OPEN = 289,      /* CURLY_BRACKET_OPEN  */
    CURLY_BRACKET_CLOSE = 290,     /* CURLY_BRACKET_CLOSE  */
    SQUARE_BRACKET_OPEN = 291,     /* SQUARE_BRACKET_OPEN  */
    SQUARE_BRACKET_CLOSE = 292,    /* SQUARE_BRACKET_CLOSE  */
    COMMA = 293,                   /* COMMA  */
    SEMICOLON = 294,               /* SEMICOLON  */
    COLON = 295,                   /* COLON  */
    DOUBLE_COLON = 296,            /* DOUBLE_COLON  */
    DOT = 297,                     /* DOT  */
    DOUBLE_DOT = 298,              /* DOUBLE_DOT  */
    OTHER = 299,                   /* OTHER  */
    IDENTIFIER = 300,              /* IDENTIFIER  */
    STRING_TOKEN = 301,            /* STRING_TOKEN  */
    INTCONST = 302,                /* INTCONST  */
    FLOATCONST = 303,              /* FLOATCONST  */
    IFX = 304,                     /* IFX  */
    UMINUS = 305                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "parser.y"

    char* strVal;
    int intVal;
    float floatVal;
    struct expr* exprVal;
    struct statement* statementVal;
    struct call* callVal;

#line 176 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
