#pragma once
#include "types.hpp"
#include "memory.hpp"
#include "parser.hpp"

class processor {
public:
    processor(u64 data_size);

    void execute(std::vector<instruction> instructions);
    memory mem;
    bool done = false;

/**
 * instruction functions
 */
    void operation(instruction inst);

    inline void op_add(instruction inst);
    inline void op_sub(instruction inst);
    inline void op_mul(instruction inst);
    inline void op_div(instruction inst);
    inline void op_mod(instruction inst);
    inline void op_nand(instruction inst);
    inline void op_and(instruction inst);
    inline void op_xnor(instruction inst);
    inline void op_xor(instruction inst);
    inline void op_nor(instruction inst);
    inline void op_or(instruction inst);
    inline void op_not(instruction inst);
    inline void op_comp(instruction inst);
    inline void op_shr(instruction inst);
    inline void op_shl(instruction inst);
    inline void op_cmp(instruction inst);
    inline void op_swp(instruction inst);
    inline void op_mov(instruction inst);
    inline void op_set(instruction inst);
    inline void op_clr(instruction inst);
    inline void op_sw(instruction inst);
    inline void op_lw(instruction inst);
    inline void op_b(instruction inst);
    inline void op_call(instruction inst);
    inline void op_ret(instruction inst);

};
