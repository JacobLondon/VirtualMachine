%{
#include <iostream>
#include "instruction.hpp"
extern int yylex();
void yyerror(const char* s) { std::cerr << "Error - yyerror << " << s << std::endl; }
%}

%union {
    instruction* inst;
    int     token;
}

// Terminal Symbols
// Instructions
%token <token> ADD SUB MUL DIV MOD NAND AND XNOR XOR NOR OR SHR SHL CMP MOV SWP SET CLR SW LW B CALL RET
// Registers
%token <token> ZERO PC I_REG F_REG
// Immediates
%token <token> NUM
// Symbols
%token <token> LBRACKET RBRACKET COMMA POUND COLON
// ARM Suffixes
%token <token> EQ_SUFFIX NE_SUFFIX CS_SUFFIX HS_SUFFIX CC_SUFFIX LO_SUFFIX MI_SUFFIX PL_SUFFIX VS_SUFFIX HI_SUFFIX LS_SUFFIX GE_SUFFIX GT_SUFFIX LE_SUFFIX AL_SUFFIX STATUS_SUFFIX
// Custom suffixes and prefixes
%token <token> F_PREFIX N_PREFIX I_SUFFIX 
// Alias support
%token <token> ALIAS ALIAS_ID
// Error
%token <token> OTHER

%start program

%%

program
    : stmts
    ;

stmts
    : stmt
    | stmts stmt
    ;

stmt
    : expression comment NEWLINE
    | expression NEWLINE
    | comment NEWLINE
    ;

comment
    : POUND OTHER
    ;

register
    : WHITESPACE ZERO_REG
    | WHITESPACE PC_REG
    | WHITESPACE I_REG
    | WHITESPACE F_REG
    ;

immediate
    : WHITESPACE NUM
    | WHITESPACE ALIAS_ID
    ;

expression
    : itype_instruction arm_suffix register register immediate
    | rtype_instruction arm_suffix register register register
    | jtype_instruction arm_suffix register register immediate
    ;

itype_instruction
    : arithmetic_op I_SUFFIX
    | MOD I_SUFFIX
    | binary_op I_SUFFIX
    | SHR I_SUFFIX
    | SHL I_SUFFIX
    | floating_flag CMP I_SUFFIX
    | floating_flag MOV I_SUFFIX
    | SW
    | LW
    | INC
    | DEC
    | PUSH I_SUFFIX
    ;

rtype_instruction
    : arithmetic_op
    | MOD
    | binary_op
    | NOT
    | COMP
    | SHR
    | SHL
    | floating_flag CMP
    | floating_flag SWP
    | floating_flag MOV
    | floating_flag SET
    | floating_flag CLR
    | PUSH
    | POP
    ;

j_type_instruction
    : B
    | CALL
    | RET
    ;

arm_suffix
    : STATUS_SUFFIX arm_suffix_cond WHITESPACE
    | STATUS_SUFFIX WHITESPACE
    | arm_suffix_cond WHITESPACE
    | WHITESPACE
    ;

arm_suffix_cond
    : EQ_SUFFIX
    | NE_SUFFIX
    | CS_SUFFIX
    | HS_SUFFIX
    | CC_SUFFIX
    | LO_SUFFIX
    | MI_SUFFIX
    | PL_SUFFIX
    | VS_SUFFIX
    | HI_SUFFIX
    | LS_SUFFIX
    | GE_SUFFIX
    | GT_SUFFIX
    | LE_SUFFIX
    | AL_SUFFIX
    ;

floating_flag 
    : F_PREFIX
    |
    ;

arithmetic_op
    : floating_flag ADD
    | floating_flag SUB
    | floating_flag MUL
    | floating_flag DIV
    ;

binary_flag
    : B
    |
    ;

binary_op
    : binary_flag NAND
    | binary_flag AND
    | binary_flag XNOR
    | binary_flag XOR
    | binary_flag NOR
    | binary_flag OR
    ;

%%
