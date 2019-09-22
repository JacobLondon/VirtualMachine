#pragma once
#include <limits>
#include "types.hpp"
#include "memory.hpp"

enum InstructionFlags {
    NOF = 0x00,
    BITF = 0x01,
    IMMF = 0x02,
};

class Instruction {
public:
    
    Instruction(u16 opcode, bool set_status, u8 suffix, u8 target, u8 register1, u8 register2, f64 immediate, u8 flags);
    bool check_flags(u8 flag);
    std::string to_string();
    bool check_suffix(Memory &memory);
    void execute(Memory& memory);

    u16 opcode = 0;

    bool set_status = false;
    u8 flags = 0;
    u8 suffix = 0;

    u8 target;
    u8 register1;
    u8 register2;

    f64 immediate;

    void op_add(Memory& mem);
    void op_sub(Memory& mem);
    void op_mul(Memory& mem);
    void op_div(Memory& mem);
    void op_mod(Memory& mem);
    void op_nand(Memory& mem);
    void op_and(Memory& mem);
    void op_xnor(Memory& mem);
    void op_xor(Memory& mem);
    void op_nor(Memory& mem);
    void op_or(Memory& mem);
    void op_not(Memory& mem);
    void op_comp(Memory& mem);
    void op_shr(Memory& mem);
    void op_shl(Memory& mem);
    void op_cmp(Memory& mem);
    void op_swp(Memory& mem);
    void op_mov(Memory& mem);
    void op_set(Memory& mem);
    void op_clr(Memory& mem);
    void op_sw(Memory& mem);
    void op_lw(Memory& mem);
    void op_inc(Memory & mem);
    void op_dec(Memory & mem);
    void op_push(Memory & mem);
    void op_pop(Memory & mem);
    void op_jmp(Memory& mem);
    void op_call(Memory& mem);
    void op_ret(Memory& mem);

};

auto reg_increase = [](Memory& mem, u8 reg, auto value)
{
    if (reg >= REG_COUNT)
        mem.fregfile[reg - REG_COUNT] = mem.fregfile[reg - REG_COUNT] + value;
    else
        mem.iregfile[reg] = mem.iregfile[reg] + value;
};

auto reg_set = [](Memory& mem, u8 reg, auto value)
{
    if (reg >= REG_COUNT)
        mem.fregfile[reg - REG_COUNT] = value;
    else
        mem.iregfile[reg] = value;
};

auto reg_at = [](Memory& mem, u8 reg, auto value)
{
    return reg >= REG_COUNT
        ? mem.fregfile[reg - REG_COUNT]
        : mem.iregfile[reg];
};

auto reg_max = [](u8 reg)
{
    return reg >= REG_COUNT
        ? std::numeric_limits<f64>::max()
        : std::numeric_limits<s64>::max();
};

auto reg_min = [](u8 reg)
{
    return reg >= REG_COUNT
        ? std::numeric_limits<f64>::min()
        : std::numeric_limits<s64>::min();
};

#define REG_SET(reg, mem, value) do { \
    if (reg >= REG_COUNT) \
        mem.fregfile[reg - REG_COUNT] = value; \
    else \
        mem.iregfile[reg] = value; \
} while (0)

#define REG_AT(reg, mem) \
    (reg >= REG_COUNT  \
    ? mem.fregfile[reg - REG_COUNT] \
    : mem.iregfile[reg])

#define REG_MAX(reg) \
    (reg >= REG_COUNT \
    ? std::numeric_limits<f64>::max() \
    : std::numeric_limits<s64>::max())

#define REG_MIN(reg) \
    (reg >= REG_COUNT \
    ? std::numeric_limits<f64>::min() \
    : std::numeric_limits<s64>::min())
