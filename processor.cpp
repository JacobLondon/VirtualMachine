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

void processor::operation(rtype inst)
{
    instruction *nist = &inst;

    if (!mem.suffix(nist))
        return;

    switch (inst.opcode) {
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
    default:
        std::cerr << "Error - Unexpected opcode: " << inst.opcode << std::endl;
        exit(-1);
    }

    if (inst.status) {
        mem.set_flags(mem.iregfile[inst.register1 - inst.register2]);
    }
}

void processor::operation(itype<s64> inst)
{
    instruction *nist = &inst;

    if (!mem.suffix(nist))
        return;

    switch (inst.opcode) {
    case LI:  op_li(inst);  break;
    case SET: op_set(inst); break;
    case CLR: op_clr(inst); break;
    case SW:  op_sw(inst);  break;
    case LW:  op_lw(inst);  break;
    default:
        std::cerr << "Error - Unexpected opcode: " << inst.opcode << std::endl;
        exit(-1);
    }
}

void processor::operation(itype<f64> inst)
{
    // TODO
}

void processor::operation(jtype inst)
{
    instruction *nist = &inst;

    if (!mem.suffix(nist))
        return;

    switch (inst.opcode) {
    case B:    op_b(inst);    break;
    case CALL: op_call(inst); break;
    case RET:  op_ret(inst);  break;
    default:
        std::cerr << "Error - Unexpected opcode: " << inst.opcode << std::endl;
        exit(-1);
    }
}

void processor::op_add(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] + mem.iregfile[inst.register2];
}

void processor::op_sub(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] - mem.iregfile[inst.register2];
}

void processor::op_mul(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] * mem.iregfile[inst.register2];
}

void processor::op_div(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] / mem.iregfile[inst.register2];
}

void processor::op_mod(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] % mem.iregfile[inst.register2];
}

void processor::op_nand(rtype inst)
{
    mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] & mem.iregfile[inst.register2]);
}

void processor::op_and(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] & mem.iregfile[inst.register2];
}

void processor::op_xnor(rtype inst)
{
    mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] ^ mem.iregfile[inst.register2]);
}

void processor::op_xor(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] ^ mem.iregfile[inst.register2];
}

void processor::op_nor(rtype inst)
{
    mem.iregfile[inst.target] = ~(mem.iregfile[inst.register1] | mem.iregfile[inst.register2]);
}

void processor::op_or(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] | mem.iregfile[inst.register2];
}

void processor::op_shr(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] >> mem.iregfile[inst.register2];
}

void processor::op_shl(rtype inst)
{
    mem.iregfile[inst.target] = mem.iregfile[inst.register1] << mem.iregfile[inst.register2];
}

void processor::op_cmp(rtype inst)
{
    inst.status = true;
}

void processor::op_mov(rtype inst)
{
    mem.iregfile[inst.register1] = mem.iregfile[inst.register2];
}

void processor::op_swp(rtype inst)
{
    std::swap(mem.iregfile[inst.register1], mem.iregfile[inst.register2]);
}

void processor::op_li(itype<s64> inst)
{
    mem.iregfile[inst.target] = inst.immediate;
}

void processor::op_set(itype<s64> inst)
{
    mem.iregfile[inst.target] = INT64_MAX;
}

void processor::op_clr(itype<s64> inst)
{
    mem.iregfile[inst.target] = 0;
}

void processor::op_sw(itype<s64> inst)
{
    mem.dmem[inst.immediate] = mem.iregfile[inst.target];
}

void processor::op_lw(itype<s64> inst)
{
    mem.iregfile[inst.target] = mem.dmem[inst.immediate];
}

void processor::op_b(jtype inst)
{
    mem.pc = inst.address;
}

void processor::op_call(jtype inst)
{
    mem.stack.push(mem.pc);
    mem.pc = inst.address;
}

void processor::op_ret(jtype inst)
{
    mem.pc = mem.stack.top();
    mem.stack.pop();
}
