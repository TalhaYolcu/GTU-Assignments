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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    COMMENT = 258,
    OP_PLUS = 259,
    OP_MINUS = 260,
    OP_DIV = 261,
    OP_MULT = 262,
    OP_OP = 263,
    OP_CP = 264,
    OP_DBLMULT = 265,
    OP_OC = 266,
    OP_TR = 267,
    OP_COMMA = 268,
    KW_AND = 269,
    KW_OR = 270,
    KW_NOT = 271,
    KW_EQUAL = 272,
    KW_LESS = 273,
    KW_NIL = 274,
    KW_LIST = 275,
    KW_APPEND = 276,
    KW_CONCAT = 277,
    KW_SET = 278,
    KW_DEFFUN = 279,
    KW_FOR = 280,
    KW_WHILE = 281,
    KW_IF = 282,
    KW_EXIT = 283,
    KW_LOAD = 284,
    KW_DISP = 285,
    KW_TRUE = 286,
    KW_FALSE = 287,
    NEWLINE = 288,
    KW_DEFVAR = 289,
    VALUE = 290,
    ID = 291,
    STRING = 292
  };
#endif
/* Tokens.  */
#define COMMENT 258
#define OP_PLUS 259
#define OP_MINUS 260
#define OP_DIV 261
#define OP_MULT 262
#define OP_OP 263
#define OP_CP 264
#define OP_DBLMULT 265
#define OP_OC 266
#define OP_TR 267
#define OP_COMMA 268
#define KW_AND 269
#define KW_OR 270
#define KW_NOT 271
#define KW_EQUAL 272
#define KW_LESS 273
#define KW_NIL 274
#define KW_LIST 275
#define KW_APPEND 276
#define KW_CONCAT 277
#define KW_SET 278
#define KW_DEFFUN 279
#define KW_FOR 280
#define KW_WHILE 281
#define KW_IF 282
#define KW_EXIT 283
#define KW_LOAD 284
#define KW_DISP 285
#define KW_TRUE 286
#define KW_FALSE 287
#define NEWLINE 288
#define KW_DEFVAR 289
#define VALUE 290
#define ID 291
#define STRING 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "gpp_interpreter.y"

    char id[20];
    int ival;
    int *ivals;
    char*string;

#line 138 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
