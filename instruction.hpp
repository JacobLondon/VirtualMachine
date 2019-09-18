#pragma once
#include "types.hpp"
#include "memory.hpp"

enum RegisterFlags {
    NOF = 0x00,
    BITF = 0x01,
    FLOATF = 0x02,
    INTF = 0x04,
    IMMF = 0x08,
};

class RegisterRef {
public:
    RegisterRef();
    RegisterRef(u8 address, u8 flags);
    u8 address;
    u8 flags;
    bool check_flags(u8 flag);
};

class Instruction {
public:
    
    Instruction(u16 opcode, bool set_status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, f64 immediate, u8 flags);
    // TODO This doesn't work correctly
    bool check_flags(u8 flag);
    std::string to_string();
    bool check_suffix(Memory &memory);
    void execute(Memory& memory);

    u16 opcode = 0;

    bool set_status = false;
    u8 flags = 0;
    u8 suffix = 0;

    RegisterRef target;
    RegisterRef register1;
    RegisterRef register2;

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
    void op_b(Memory& mem);
    void op_call(Memory& mem);
    void op_ret(Memory& mem);
};

#define REG_SET(reg, mem, value) do { \
    if (reg.check_flags(FLOATF)) \
        mem.fregfile[reg.address] = value; \
    else \
        mem.iregfile[reg.address] = value; \
} while (0)

#define REG_AT(reg, mem) \
    (reg.check_flags(FLOATF) \
    ? mem.fregfile[reg.address] \
    : mem.iregfile[reg.address])

#define REG_MAX(reg) \
    (reg.check_flags(FLOATF) \
    ? std::numeric_limits<f64>::max() \
    : std::numeric_limits<s64>::max())

#define REG_MIN(reg) \
    (reg.check_flags(FLOATF) \
    ? std::numeric_limits<f64>::min() \
    : std::numeric_limits<s64>::min())
