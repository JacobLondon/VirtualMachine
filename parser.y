%{
#include "instruction.h"
%}

%union {
    jtype*  jinst;
    itype*  iinst;
    rtype*  rinst;

    int     token;
}

// terminal symbols
%token <token> ADD SUB MUL DIV MOD NAND AND XNOR XOR NOR OR SHR SRA SHL ROR ROL CMP MOV SWP MOV SET CLR SW LW B CALL RET
%token <token> EQ NE CS HS CC LO MI PL VS HI LS GE GT LE AL
%token <token> ZERO PC R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 R16 R17 R18 R19 R20 R21 R22 R23 R24 R25 R26 R27 R28 R29
%token <token> STATUS

// non terminal symbols
%

%start program

%%

program:
    stmts
    ;

stmts:
      stmt
    | stmts stmt
    ;

stmt:
      comment
    | label
    | instruction
    ;

comment:
    POUND OTHER
    ;

label:
    OTHER COLON
    ;

instruction:
      opcode STATUS SUFFIX register register register
    | opcode STATUS SUFFIX register NUM
    | opcode STATUS SUFFIX NUM
    ;

%%