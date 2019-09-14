%{
#include <iostream>
#include <cstdlib>
#include "parser.hpp"
%}

%option noyywrap
%option yylineno

whitespace [ \t]
newline [ \t\r\n]
digit [0-9]
hexdigit [0-9a-fA-F]
binarydigit [01]
letter [a-zA-Z]
alphanum [a-zA-Z0-9]

%%

    /* Syntax */
{whitespace}*       return WHITESPACE;
{newline}*          return NEWLINE;
[1-9]{digit}+       return NUM;
"0x"{hexdigit}+     return NUM;
"0b"{binarydigit}+  return NUM;
"["                 return LBRACKET;
"]"                 return RBRACKET;
","                 return COMMA;
"#"                 return POUND;
":"                 return COLON;

    /* Instructions */
"nop"               return NOP;
"add"               return ADD;
"sub"               return SUB;
"mul"               return MUL;
"div"               return DIV;
"mod"               return MOD;
"nand"              return NAND;
"and"               return AND;
"xnor"              return XNOR;
"xor"               return XOR;
"nor"               return NOR;
"or"                return OR;
"not"               return NOT;
"comp"              return COMP;
"shr"               return SHR;
"shl"               return SHL;
"cmp"               return CMP;
"swp"               return SWP;
"mov"               return MOV;
"set"               return SET;
"clr"               return CLR;
"sw"                return SW;
"lw"                return LW;
"b"                 return B
"call"              return CALL;
"ret"               return RET;

    /* Registers */
"zero"              return ZERO_REG;
"pc"                return   PC_REG;
"r"[0-3]?[0-9]      return    I_REG;
"f"[0-3]?[0-9]      return    F_REG;

    /* ARM Suffixes */
"eq"                return EQ_SUFFIX;
"ne"                return NE_SUFFIX;
"cs"                return CS_SUFFIX;
"hs"                return HS_SUFFIX;
"cc"                return CC_SUFFIX;
"lo"                return LO_SUFFIX;
"mi"                return MI_SUFFIX;
"pl"                return PL_SUFFIX;
"vs"                return VS_SUFFIX;
"vc"                return VC_SUFFIX;
"hi"                return HI_SUFFIX;
"ls"                return LS_SUFFIX;
"ge"                return GE_SUFFIX;
"lt"                return LT_SUFFIX;
"gt"                return GT_SUFFIX;
"le"                return LE_SUFFIX;
"al"                return AL_SUFFIX;
"s"                 return STATUS_SUFFIX;

    /* Aliases */
"alias"             return ALIAS;
{letter}{alphanum}* return ALIAS_ID;

    /* Suffixes and prefixes */
"f"                 return F_PREFIX;
"n"                 return N_PREFIX;
"i"                 return I_SUFFIX;
.                   return OTHER;

%%
