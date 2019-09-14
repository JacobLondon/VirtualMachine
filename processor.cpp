#include <cmath>
#include <limits>
#include "processor.hpp"

processor::processor(u64 data_size)
    : mem(data_size)
{
    
}

void processor::execute(std::vector<instruction> instructions)
{
    mem.imem = instructions;
}

/**
 * instruction functions
 */

void processor::operation(instruction inst)
{
    if (!mem.suffix(inst))
        return;

    switch (inst.opcode) {
    // r type
    case ADD:  op_add(inst);  break;
    case SUB:  op_sub(inst);  break;
    case MUL:  op_mul(inst);  break;
    case DIV:  op_div(inst);  break;
    case MOD:  op_mod(inst);  break;
    case NAND: op_nand(inst); break;
    case AND:  op_and(inst);  break;
    case XNOR: op_xnor(inst); break;
    case XOR:  op_xor(inst);  break;
    case NOR:  op_nor(inst);  break;
    case OR:   op_or(inst);   break;
    case NOT:  op_not(inst);  break;
    case COMP: op_comp(inst); break;
    case SHR:  op_shr(inst);  break;
    case SHL:  op_shl(inst);  break;
    case CMP:  op_cmp(inst);  break;
    case SWP:  op_swp(inst);  break;
    case MOV:  op_mov(inst);  break;
    // i type
    case SET:  op_set(inst);  break;
    case CLR:  op_clr(inst);  break;
    case SW:   op_sw(inst);   break;
    case LW:   op_lw(inst);   break;
    // j type
    case B:    op_b(inst);    break;
    case CALL: op_call(inst); break;
    case RET:  op_ret(inst);  break;
    default:
        std::cerr << "Error - Unexpected opcode: " << inst.opcode << std::endl;
        exit(-1);
    }

    if (inst.status) {
        if (inst.floating)
            mem.set_flags(mem.fregfile[inst.register1] - mem.fregfile[inst.register2]);
        else
            mem.set_flags(mem.iregfile[inst.register1] - mem.iregfile[inst.register2]);
    }
}

#define MACOP(op) \
    if (!inst.floating) { \
        if (inst.imm) \
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] op inst.immediate.integer; \
        else \
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] op mem.iregfile[inst.register2]; \
    } \
    else { \
        if (inst.imm) \
            mem.fregfile[inst.target] = mem.fregfile[inst.register1] op inst.immediate.floating; \
        else \
            mem.fregfile[inst.target] = mem.fregfile[inst.register1] op mem.fregfile[inst.register2]; \
    }

void processor::op_add(instruction inst)
{
    MACOP(+);
}

void processor::op_sub(instruction inst)
{
    MACOP(-);
}

void processor::op_mul(instruction inst)
{
    MACOP(*);
}

void processor::op_div(instruction inst)
{
    MACOP(/);
}

void processor::op_mod(instruction inst)
{
    if (!inst.floating) {
        if (inst.imm && inst.bitwise)
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] % inst.immediate.integer;
        else
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] % mem.iregfile[inst.register2];
    }
    else {
        if (inst.imm)
            mem.fregfile[inst.target] = fmod(mem.fregfile[inst.register1], inst.immediate.floating);
        else
            mem.fregfile[inst.target] = fmod(mem.fregfile[inst.register1], mem.fregfile[inst.register2]);
    }
}

void processor::op_nand(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'nand' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.bitwise) {
        if (inst.imm)
            mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] & inst.immediate.integer);
        else
            mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] & mem.iregfile[inst.register2]);
    }
    else {
        if (inst.imm)
            mem.iregfile[inst.target] = !(mem.iregfile[inst.register1] && inst.immediate.integer);
        else
            mem.iregfile[inst.target] = !(mem.iregfile[inst.register1] && mem.iregfile[inst.register2]);
    }
}

void processor::op_and(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'and' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.bitwise) {
        if (inst.imm)
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] & inst.immediate.integer;
        else
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] & mem.iregfile[inst.register2];
    }
    else {
        if (inst.imm)
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] && inst.immediate.integer;
        else
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] && mem.iregfile[inst.register2];
    }
}

void processor::op_xnor(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.bitwise) {
        if (inst.imm)
            mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] ^ inst.immediate.integer);
        else
            mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] ^ mem.iregfile[inst.register2]);
    }
    else {
        if (inst.imm)
            mem.iregfile[inst.target] = (mem.iregfile[inst.register1] == 0 && inst.immediate.integer == 0)
                                        || (mem.iregfile[inst.register1] != 0 && inst.immediate.integer != 0);
        else
            mem.iregfile[inst.target] = (mem.iregfile[inst.register1] == 0 && mem.iregfile[inst.register2] == 0)
                                        || (mem.iregfile[inst.register1] != 0 && mem.iregfile[inst.register2] != 0);
    }
}

void processor::op_xor(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.bitwise) {
        if (inst.imm)
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] ^ inst.immediate.integer;
        else
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] ^ mem.iregfile[inst.register2];
    }
    else {
        if (inst.imm)
            mem.iregfile[inst.target] = (mem.iregfile[inst.register1] == 0 && inst.immediate.integer != 0)
                                        || (mem.iregfile[inst.register1] != 0 && inst.immediate.integer == 0);
        else
            mem.iregfile[inst.target] = (mem.iregfile[inst.register1] == 0 && mem.iregfile[inst.register2] != 0)
                                        || (mem.iregfile[inst.register1] != 0 && mem.iregfile[inst.register2] == 0);
    }
}

void processor::op_nor(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.bitwise) {
        if (inst.imm)
            mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] | inst.immediate.integer);
        else
            mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] | mem.iregfile[inst.register2]);
    }
    else {
        if (inst.imm)
            mem.iregfile[inst.target] = !(mem.iregfile[inst.register1] || inst.immediate.integer);
        else
            mem.iregfile[inst.target] = !(mem.iregfile[inst.register1] || mem.iregfile[inst.register2]);
    }
}

void processor::op_or(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.bitwise) {
        if (inst.imm)
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] | inst.immediate.integer;
        else
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] | mem.iregfile[inst.register2];
    }
    else {
        if (inst.imm)
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] || inst.immediate.integer;
        else
            mem.iregfile[inst.target] = mem.iregfile[inst.register1] || mem.iregfile[inst.register2];
    }
}

void processor::op_not(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.floating) {
        mem.iregfile[inst.target] = !mem.iregfile[inst.register1];
    }
}

void processor::op_comp(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (!inst.floating) {
        mem.iregfile[inst.target] = ~mem.iregfile[inst.register1];
    }
}

void processor::op_shr(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.imm) {
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] >> inst.immediate.integer;
    }
    else {
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] >> mem.iregfile[inst.register2];
    }
}

void processor::op_shl(instruction inst)
{
    if (inst.floating) {
        std::cerr << "Error - Invalid operation 'xnor' on " << inst.to_string() << std::endl;
        exit(-1);
    }

    if (inst.imm) {
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] << inst.immediate.integer;
    }
    else {
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] << mem.iregfile[inst.register2];
    }
}

void processor::op_cmp(instruction inst)
{
    if (inst.floating)
        mem.set_flags(mem.fregfile[inst.register1] - mem.fregfile[inst.register2]);
    else
        mem.set_flags(mem.iregfile[inst.register1] - mem.iregfile[inst.register2]);

}

void processor::op_swp(instruction inst)
{
    if (inst.floating)
        std::swap(mem.fregfile[inst.register1], mem.fregfile[inst.register2]);
    else
        std::swap(mem.iregfile[inst.register1], mem.iregfile[inst.register2]);
}

void processor::op_mov(instruction inst)
{
    if (inst.floating) {
        if (inst.imm)
            mem.fregfile[inst.register1] = inst.immediate.floating;
        else
            mem.fregfile[inst.register1] = mem.fregfile[inst.register2];
    }
    else {
        if (inst.imm)
            mem.iregfile[inst.register1] = inst.immediate.integer;
        else
            mem.iregfile[inst.register1] = mem.iregfile[inst.register2];
    }
}

void processor::op_set(instruction inst)
{
    if (inst.floating)
        mem.fregfile[inst.target] = std::numeric_limits<f64>::max();
    else
        mem.iregfile[inst.target] = std::numeric_limits<s64>::max();
}

void processor::op_clr(instruction inst)
{
    if (inst.floating)
        mem.fregfile[inst.target] = 0;
    else
        mem.iregfile[inst.target] = 0;
}

void processor::op_sw(instruction inst)
{
    mem.dmem[inst.immediate.address] = reinterpret_cast<s64&>(mem.iregfile[inst.target]);
}

void processor::op_lw(instruction inst)
{
    if (inst.floating)
        mem.fregfile[inst.target] = reinterpret_cast<f64&>(mem.dmem[inst.immediate.address]);
    else
        mem.iregfile[inst.target] = mem.dmem[inst.immediate.address];
}

void processor::op_b(instruction inst)
{
    mem.pc = mem.iregfile[inst.register1] + inst.immediate.address;
}

void processor::op_call(instruction inst)
{
    mem.call_stack.push(mem.pc);
    mem.pc = mem.iregfile[inst.register1] + inst.immediate.address;
}

void processor::op_ret(instruction inst)
{
    mem.pc = mem.call_stack.top();
    mem.call_stack.pop();
}
