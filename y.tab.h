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
     COMMA = 258,
     SEMICOLON = 259,
     LPARENTHESIS = 260,
     RPARENTHESIS = 261,
     LBRACKET = 262,
     RBRACKET = 263,
     LBRACE = 264,
     RBRACE = 265,
     DOT = 266,
     PLUS = 267,
     MINUS = 268,
     TIMES = 269,
     DIVIDE = 270,
     LTE = 271,
     GTE = 272,
     EQ = 273,
     NEQ = 274,
     GT = 275,
     LT = 276,
     AND = 277,
     OR = 278,
     ASSIGN = 279,
     ARRAY = 280,
     IF = 281,
     THEN = 282,
     ELSE = 283,
     WHILE = 284,
     FOR = 285,
     TO = 286,
     DO = 287,
     LET = 288,
     IN = 289,
     END = 290,
     OF = 291,
     BREAK = 292,
     NIL = 293,
     FUNCTION = 294,
     VAR = 295,
     TYPE = 296,
     NEW = 297,
     ID = 298,
     INTEGER = 299,
     COLON = 300,
     STRING = 301
   };
#endif
/* Tokens.  */
#define COMMA 258
#define SEMICOLON 259
#define LPARENTHESIS 260
#define RPARENTHESIS 261
#define LBRACKET 262
#define RBRACKET 263
#define LBRACE 264
#define RBRACE 265
#define DOT 266
#define PLUS 267
#define MINUS 268
#define TIMES 269
#define DIVIDE 270
#define LTE 271
#define GTE 272
#define EQ 273
#define NEQ 274
#define GT 275
#define LT 276
#define AND 277
#define OR 278
#define ASSIGN 279
#define ARRAY 280
#define IF 281
#define THEN 282
#define ELSE 283
#define WHILE 284
#define FOR 285
#define TO 286
#define DO 287
#define LET 288
#define IN 289
#define END 290
#define OF 291
#define BREAK 292
#define NIL 293
#define FUNCTION 294
#define VAR 295
#define TYPE 296
#define NEW 297
#define ID 298
#define INTEGER 299
#define COLON 300
#define STRING 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

