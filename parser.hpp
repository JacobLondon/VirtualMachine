/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    MOD = 262,
    NAND = 263,
    AND = 264,
    XNOR = 265,
    XOR = 266,
    NOR = 267,
    OR = 268,
    SHR = 269,
    SHL = 270,
    CMP = 271,
    MOV = 272,
    SWP = 273,
    SET = 274,
    CLR = 275,
    SW = 276,
    LW = 277,
    B = 278,
    CALL = 279,
    RET = 280,
    EQ = 281,
    NE = 282,
    CS = 283,
    HS = 284,
    CC = 285,
    LO = 286,
    MI = 287,
    PL = 288,
    VS = 289,
    HI = 290,
    LS = 291,
    GE = 292,
    GT = 293,
    LE = 294,
    AL = 295,
    ZERO = 296,
    PC = 297,
    NUM = 298,
    LBRACKET = 299,
    RBRACKET = 300,
    COMMA = 301,
    POUND = 302,
    COLON = 303,
    STATUS = 304,
    OTHER = 305
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define MOD 262
#define NAND 263
#define AND 264
#define XNOR 265
#define XOR 266
#define NOR 267
#define OR 268
#define SHR 269
#define SHL 270
#define CMP 271
#define MOV 272
#define SWP 273
#define SET 274
#define CLR 275
#define SW 276
#define LW 277
#define B 278
#define CALL 279
#define RET 280
#define EQ 281
#define NE 282
#define CS 283
#define HS 284
#define CC 285
#define LO 286
#define MI 287
#define PL 288
#define VS 289
#define HI 290
#define LS 291
#define GE 292
#define GT 293
#define LE 294
#define AL 295
#define ZERO 296
#define PC 297
#define NUM 298
#define LBRACKET 299
#define RBRACKET 300
#define COMMA 301
#define POUND 302
#define COLON 303
#define STATUS 304
#define OTHER 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 8 "parser.ypp" /* yacc.c:1909  */

    instruction* inst;
    int     token;

#line 159 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
