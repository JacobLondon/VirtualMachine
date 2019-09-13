#pragma once
#include "types.hpp"
#include "memory.hpp"

class processor {
public:
    processor(u64 data_size);

    void execute(std::vector<instruction> instructions);

    memory mem;

/**
 * instruction functions
 */
    void operation(instruction inst);

    void op_add(instruction inst);
    void op_sub(instruction inst);
    void op_mul(instruction inst);
    void op_div(instruction inst);
    void op_mod(instruction inst);
    void op_nand(instruction inst);
    void op_and(instruction inst);
    void op_xnor(instruction inst);
    void op_xor(instruction inst);
    void op_nor(instruction inst);
    void op_or(instruction inst);
    void op_shr(instruction inst);
    void op_shl(instruction inst);
    void op_cmp(instruction inst);    // target doesn't matter
    void op_mov(instruction inst);    // target doesn't matter
    void op_swp(instruction inst);    // target doesn't matter
    void op_li(instruction inst);
    void op_set(instruction inst);   // immediate doesn't matter
    void op_clr(instruction inst);   // immediate doesn't matter
    void op_sw(instruction inst);
    void op_lw(instruction inst);
    void op_b(instruction inst);
    void op_call(instruction inst);
    void op_ret(instruction inst);

};
