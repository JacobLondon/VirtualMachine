%{
#include <iostream>
#include "parser.h"
%}

%option noyywrap
%option yylineno

%%

[ \t\r\n]   ;
[0-9]+      return NUM;
"["         return LBRACKET;
"]"         return RBRACKET;
","         return COMMA;
"#"         return POUND;
":"         return COLON;
"add"       return ADD;
"sub"       return SUB;
"mul"       return MUL;
"div"       return DIV;
"mod"       return MOD;
"nand"      return NAND;
"and"       return AND;
"xnor"      return XNOR;
"xor"       return XOR;
"nor"       return NOR;
"or"        return OR;
"shr"       return SHR;
"sra"       return SRA;
"shl"       return SHL;
"ror"       return ROR;
"rol"       return ROL;
"cmp"       return CMP;
"mov"       return MOV;
"swp"       return SWP;
"mov"       return MOV;
"set"       return SET;
"clr"       return CLR;
"sw"        return SW;
"lw"        return LW;
"b"         return B;
"call"      return CALL;
"ret"       return RET;

"eq"        return EQ;
"ne"        return NE;
"cs"        return CS;
"hs"        return HS;
"cc"        return CC;
"lo"        return LO;
"mi"        return MI;
"pl"        return PL;
"vs"        return VS;
"hi"        return HI;
"ls"        return LS;
"ge"        return GE;
"gt"        return GT;
"le"        return LE;
"al"        return AL;

"zero"      return ZERO;
"pc"        return PC;
"r0"        return R0;
"r1"        return R1;
"r2"        return R2;
"r3"        return R3;
"r4"        return R4;
"r5"        return R5;
"r6"        return R6;
"r7"        return R7;
"r8"        return R8;
"r9"        return R9;
"r10"       return R10;
"r11"       return R11;
"r12"       return R12;
"r13"       return R13;
"r14"       return R14;
"r15"       return R15;
"r16"       return R16;
"r17"       return R17;
"r18"       return R18;
"r19"       return R19;
"r20"       return R20;
"r21"       return R21;
"r22"       return R22;
"r23"       return R23;
"r24"       return R24;
"r25"       return R25;
"r26"       return R26;
"r27"       return R27;
"r28"       return R28;
"r29"       return R29;

"s"         return STATUS;
.           return OTHER;


%%