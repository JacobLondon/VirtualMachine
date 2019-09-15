#pragma once
#include "types.hpp"
#include "memory.hpp"

enum RegisterFlags {
    BITF = 0x01,
    FLOATF = 0x02,
    //INTF = 0x04,
    IMMF = 0x08,
};

class RegisterRef {
public:
    RegisterRef(u8 address, u8 flags) : address{address}, flags{flags} {}
    u8 address;
    u8 flags;
    inline bool check_flags(u8 flag) { return ((flags & flag) | flag); }
};

class Instruction {
public:
    
    Instruction(u16 opcode, bool status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, s64 immediate);
    Instruction(u16 opcode, bool status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, f64 immediate);
    std::string to_string();
    inline bool check_flags(u8 flag) { return ((flags & flag) | flag); }
    bool check_suffix(Memory &memory);
    void execute(Memory& memory);

    u16 opcode = 0;

    bool status = false;
    u8 flags = 0;
    u8 suffix = 0;

    RegisterRef target;
    RegisterRef register1;
    RegisterRef register2;

    union immediate {
        s64 integer;
        f64 floating;
    } immediate;

    inline void op_add(Memory& mem);
    inline void op_sub(Memory& mem);
    inline void op_mul(Memory& mem);
    inline void op_div(Memory& mem);
    inline void op_mod(Memory& mem);
    inline void op_nand(Memory& mem);
    inline void op_and(Memory& mem);
    inline void op_xnor(Memory& mem);
    inline void op_xor(Memory& mem);
    inline void op_nor(Memory& mem);
    inline void op_or(Memory& mem);
    inline void op_not(Memory& mem);
    inline void op_comp(Memory& mem);
    inline void op_shr(Memory& mem);
    inline void op_shl(Memory& mem);
    inline void op_cmp(Memory& mem);
    inline void op_swp(Memory& mem);
    inline void op_mov(Memory& mem);
    inline void op_set(Memory& mem);
    inline void op_clr(Memory& mem);
    inline void op_sw(Memory& mem);
    inline void op_lw(Memory& mem);
    inline void op_b(Memory& mem);
    inline void op_call(Memory& mem);
    inline void op_ret(Memory& mem);
};

#define IMMEDIATE(instruction) \
    (instruction->check_flags(FLOATF) \
    ? instruction->immediate.floating \
    : instruction->immediate.integer)

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
