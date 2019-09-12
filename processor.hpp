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
    void operation(rtype inst);
    void operation(itype<s64> inst);
    void operation(itype<f64> inst);
    void operation(jtype inst);

    void op_add(rtype inst);
    void op_sub(rtype inst);
    void op_mul(rtype inst);
    void op_div(rtype inst);
    void op_mod(rtype inst);
    void op_nand(rtype inst);
    void op_and(rtype inst);
    void op_xnor(rtype inst);
    void op_xor(rtype inst);
    void op_nor(rtype inst);
    void op_or(rtype inst);
    void op_shr(rtype inst);
    void op_shl(rtype inst);
    void op_cmp(rtype inst);    // target doesn't matter
    void op_mov(rtype inst);    // target doesn't matter
    void op_swp(rtype inst);    // target doesn't matter
    void op_li(itype<s64> inst);
    void op_set(itype<s64> inst);   // immediate doesn't matter
    void op_clr(itype<s64> inst);   // immediate doesn't matter
    void op_sw(itype<s64> inst);
    void op_lw(itype<s64> inst);
    void op_b(jtype inst);
    void op_call(jtype inst);
    void op_ret(jtype inst);

};
