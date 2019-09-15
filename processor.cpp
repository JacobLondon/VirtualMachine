#include <cmath>
#include <limits>
#include "processor.hpp"

processor::processor(u64 data_size)
    : mem(data_size)
{
    // pass
}

void processor::execute(std::vector<Instruction> Instructions)
{
    done = false;
    mem.imem = Instructions;
    for (mem.pc = 0; mem.pc < mem.imem.size(); mem.pc++) {
        operation(mem.imem[mem.pc]);
    }
    done = true;
}

/**
 * Instruction functions
 */

void processor::operation(Instruction inst)
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

    if (!inst.status)
        return;
    
    if (inst.check_flags(inst.FLOAT))
        mem.set_flags(mem.fregfile[inst.register1] - mem.fregfile[inst.register2]);
    else
        mem.set_flags(mem.iregfile[inst.register1] - mem.iregfile[inst.register2]);
}

#define MATH_FOP(op) \
    if (inst.check_flags(inst.FLOAT | inst.IMM)) \
        mem.fregfile[inst.target] = mem.fregfile[inst.register1] op inst.immediate.floating; \
    else if (inst.check_flags(inst.FLOAT)) \
        mem.fregfile[inst.target] = mem.fregfile[inst.register1] op mem.fregfile[inst.register2]

#define MATH_IOP(op) \
    else if (inst.check_flags(inst.IMM)) \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op inst.immediate.integer; \
    else /* regular */ \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op mem.iregfile[inst.register2]

#define MATH_OP(op) \
    MATH_FOP(op); \
    MATH_IOP(op)

#define FLOAT_CHK(message) \
    if (inst.check_flags(inst.FLOAT)) { \
        std::cerr << "Error - Invalid operation '" << message << "' on " << inst.to_string() << std::endl; \
        exit(-1); \
    } else

static inline void check_float(Instruction& inst, std::string message)
{
    if (inst.check_flags(inst.FLOAT)) {
        std::cerr << "Error - Invalid operation '" << message << "' on " << inst.to_string() << std::endl;
        exit(-1);
    }
}

#define LOGBIT_OP(op, message) \
    FLOAT_CHK(message); \
    if (inst.check_flags(inst.BIT | inst.IMM)) \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op inst.immediate.integer; \
    else if (inst.check_flags(inst.BIT)) \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op mem.iregfile[inst.register2]; \
    else if (inst.check_flags(inst.IMM)) \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op##op inst.immediate.integer; \
    else /* regular */ \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op##op mem.iregfile[inst.register2]

#define BIT_OP(op, message) \
    FLOAT_CHK(message); \
    if (inst.check_flags(inst.IMM)) \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op inst.immediate.integer; \
    else \
        mem.iregfile[inst.target] = mem.iregfile[inst.register1] op mem.iregfile[inst.register2]

void processor::op_add(Instruction inst)
{
    MATH_OP(+);
}

void processor::op_sub(Instruction inst)
{
    MATH_OP(-);
}

void processor::op_mul(Instruction inst)
{
    MATH_OP(*);
}

void processor::op_div(Instruction inst)
{
    MATH_OP(/);
}

void processor::op_mod(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT | inst.IMM))
        mem.fregfile[inst.target] = fmod(mem.fregfile[inst.register1], mem.fregfile[inst.register2]);
    else if (inst.check_flags(inst.FLOAT))
        mem.fregfile[inst.target] = fmod(mem.fregfile[inst.register1], inst.immediate.floating);
    MATH_IOP(%);
}

void processor::op_and(Instruction inst)
{
    LOGBIT_OP(&, "and");
}

void processor::op_xor(Instruction inst)
{
    BIT_OP(^, "xor");
}

void processor::op_or(Instruction inst)
{
    LOGBIT_OP(|, "or");
}

void processor::op_not(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT))
        mem.fregfile[inst.target] = !mem.fregfile[inst.register1];
    else
        mem.iregfile[inst.target] = !mem.iregfile[inst.register1];
}

void processor::op_comp(Instruction inst)
{
    FLOAT_CHK("comp")

    mem.iregfile[inst.target] = ~mem.iregfile[inst.register1];
}

void processor::op_shr(Instruction inst)
{
    BIT_OP(>>, "shr");
}

void processor::op_shl(Instruction inst)
{
    BIT_OP(<<, "shl");
}

void processor::op_cmp(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT))
        mem.set_flags(mem.fregfile[inst.register1] - mem.fregfile[inst.register2]);
    else
        mem.set_flags(mem.iregfile[inst.register1] - mem.iregfile[inst.register2]);
}

void processor::op_swp(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT))
        std::swap(mem.fregfile[inst.register1], mem.fregfile[inst.register2]);
    else
        std::swap(mem.iregfile[inst.register1], mem.iregfile[inst.register2]);
}

void processor::op_mov(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT | inst.IMM))
        mem.fregfile[inst.register1] = inst.immediate.floating;
    else if (inst.check_flags(inst.FLOAT))
        mem.fregfile[inst.register1] = mem.fregfile[inst.register2];
    else if (inst.check_flags(inst.IMM))
        mem.iregfile[inst.register1] = inst.immediate.integer;
    else // regular
        mem.iregfile[inst.register1] = mem.iregfile[inst.register2];
}

void processor::op_set(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT))
        mem.fregfile[inst.target] = std::numeric_limits<f64>::max();
    else
        mem.iregfile[inst.target] = std::numeric_limits<s64>::max();
}

void processor::op_clr(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT))
        mem.fregfile[inst.target] = 0;
    else
        mem.iregfile[inst.target] = 0;
}

void processor::op_sw(Instruction inst)
{
    mem.dmem[inst.immediate.address] = reinterpret_cast<s64&>(mem.iregfile[inst.target]);
}

void processor::op_lw(Instruction inst)
{
    if (inst.check_flags(inst.FLOAT))
        mem.fregfile[inst.target] = reinterpret_cast<f64&>(mem.dmem[inst.immediate.address]);
    else
        mem.iregfile[inst.target] = mem.dmem[inst.immediate.address];
}

void processor::op_b(Instruction inst)
{
    mem.pc = mem.iregfile[inst.register1] + inst.immediate.address;
}

void processor::op_call(Instruction inst)
{
    mem.call_stack.push(mem.pc);
    mem.pc = mem.iregfile[inst.register1] + inst.immediate.address;
}

void processor::op_ret(Instruction inst)
{
    mem.pc = mem.call_stack.top();
    mem.call_stack.pop();
}
