#pragma once
#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "types.hpp"
#include "memory.hpp"

enum InstructionFlags {
    NOF = 0x00,
    BITF = 0x01,
    IMMF = 0x02,
};

class Instruction {
public:
    
    uint16_t opcode = 0;
    bool     set_status = false;
    uint8_t  suffix = 0;
    uint8_t target;
    uint8_t register1;
    uint8_t register2;
    Float immediate;
    uint8_t flags = 0;

    Memory *mem;

    Instruction(
        uint16_t opcode,
        bool     set_status,
        uint8_t  suffix,
        uint8_t  target,
        uint8_t  register1,
        uint8_t  register2,
        Float    immediate,
        uint8_t  flags
    );
    bool check_flags(uint8_t flag);
    std::string to_string();
    bool check_suffix();
    void execute();

    void op_add();
    void op_sub();
    void op_mul();
    void op_div();
    void op_mod();
    void op_nand();
    void op_and();
    void op_xnor();
    void op_xor();
    void op_nor();
    void op_or();
    void op_not();
    void op_comp();
    void op_shr();
    void op_shl();
    void op_cmp();
    void op_swp();
    void op_mov();
    void op_set();
    void op_clr();
    void op_sw();
    void op_lw();
    void op_inc();
    void op_dec();
    void op_push();
    void op_pop();
    void op_jmp();
    void op_call();
    void op_ret();
};

auto reg_increase = [](Memory *mem, uint8_t reg, auto value)
{
    if (reg >= REG_COUNT)
        mem->fregfile[reg - REG_COUNT] = mem->fregfile[reg - REG_COUNT] + value;
    else
        mem->iregfile[reg] = mem->iregfile[reg] + value;
};

auto reg_set = [](Memory *mem, uint8_t reg, auto value)
{
    if (reg >= REG_COUNT)
        mem->fregfile[reg - REG_COUNT] = value;
    else
        mem->iregfile[reg] = value;
};

auto reg_at = [](Memory *mem, uint8_t reg)
{
    return reg >= REG_COUNT
        ? mem->fregfile[reg - REG_COUNT]
        : mem->iregfile[reg];
};

#endif // INSTRUCTION_H_