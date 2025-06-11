/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 160 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

