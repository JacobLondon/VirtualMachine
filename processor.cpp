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
    case SHR:  op_shr(inst);  break;
    case SHL:  op_shl(inst);  break;
    case CMP:  op_cmp(inst);  break;
    case MOV:  op_mov(inst);  break;
    case SWP:  op_swp(inst);  break;
    // i type
    case LI:  op_li(inst);  break;
    case SET: op_set(inst); break;
    case CLR: op_clr(inst); break;
    case SW:  op_sw(inst);  break;
    case LW:  op_lw(inst);  break;
    // j type
    case B:    op_b(inst);    break;
    case CALL: op_call(inst); break;
    case RET:  op_ret(inst);  break;
    default:
        std::cerr << "Error - Unexpected opcode: " << inst.opcode << std::endl;
        exit(-1);
    }

    if (inst.status) {
        mem.set_flags(mem.iregfile[inst.register1 - inst.register2]);
    }
}

void processor::op_add(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] + mem.iregfile[inst.register2];
}

void processor::op_sub(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] - mem.iregfile[inst.register2];
}

void processor::op_mul(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] * mem.iregfile[inst.register2];
}

void processor::op_div(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] / mem.iregfile[inst.register2];
}

void processor::op_mod(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] % mem.iregfile[inst.register2];
}

void processor::op_nand(instruction inst)
{
    mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] & mem.iregfile[inst.register2]);
}

void processor::op_and(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] & mem.iregfile[inst.register2];
}

void processor::op_xnor(instruction inst)
{
    mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] ^ mem.iregfile[inst.register2]);
}

void processor::op_xor(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] ^ mem.iregfile[inst.register2];
}

void processor::op_nor(instruction inst)
{
    mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] | mem.iregfile[inst.register2]);
}

void processor::op_or(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] | mem.iregfile[inst.register2];
}

void processor::op_shr(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] >> mem.iregfile[inst.register2];
}

void processor::op_shl(instruction inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] << mem.iregfile[inst.register2];
}

void processor::op_cmp(instruction inst)
{
    inst.status = true;
}

void processor::op_mov(instruction inst)
{
    mem.iregfile[inst.register1] = mem.iregfile[inst.register2];
}

void processor::op_swp(instruction inst)
{
    std::swap(mem.iregfile[inst.register1], mem.iregfile[inst.register2]);
}

void processor::op_li(instruction inst)
{
    mem.iregfile[inst.target] = inst.immediate.integer;
}

void processor::op_set(instruction inst)
{
    mem.iregfile[inst.target] = INT64_MAX;
}

void processor::op_clr(instruction inst)
{
    mem.iregfile[inst.target] = 0;
}

void processor::op_sw(instruction inst)
{
    mem.dmem[inst.immediate.address] = mem.iregfile[inst.target];
}

void processor::op_lw(instruction inst)
{
    mem.iregfile[inst.target] = mem.dmem[inst.immediate.address];
}

void processor::op_b(instruction inst)
{
    mem.pc = inst.immediate.address;
}

void processor::op_call(instruction inst)
{
    mem.call_stack.push(mem.pc);
    mem.pc = inst.immediate.address;
}

void processor::op_ret(instruction inst)
{
    mem.pc = mem.call_stack.top();
    mem.call_stack.pop();
}
