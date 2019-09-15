#pragma once
#include "types.hpp"
#include "memory.hpp"

enum RegisterFlags {
    NONE = 0x00,
    BIT = 0x01,
    FLOAT = 0x02,
    IMM = 0x04,
};

class RegisterRef {
public:
    RegisterRef(u8 address, u8 flags) : address{address}, flags{flags} {}
    u8 address;
    u8 flags;
};

class Instruction {
public:
    
    Instruction(u16 opcode, bool status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, s64 immediate);
    Instruction(u16 opcode, bool status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, f64 immediate);
    std::string to_string();
    inline bool check_flags(u8 flag);
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
    
    inline void set_target(s64 value, Memory& mem);
    inline void set_target(f64 value, Memory& mem);
    inline void set_target(bool value, Memory& mem);

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

#define REG_TARGET(instruction, memory) \
    (instruction->check_flags(FLOAT) \
    ? memory.fregfile[instruction->target.address] \
    : memory.iregfile[instruction->target.address])

#define REG_1(instruction, memory) \
    (instruction->check_flags(FLOAT) \
    ? memory.fregfile[instruction->register1.address] \
    : memory.iregfile[instruction->register1.address])

#define REG_2(instruction, memory) \
    (instruction->check_flags(FLOAT) \
    ? memory.fregfile[instruction->register2.address] \
    : memory.iregfile[instruction->register2.address])

#define IMMEDIATE(instruction) \
    (instruction->check_flags(FLOAT) \
    ? instruction->immediate.floating \
    : instruction->immediate.integer)
