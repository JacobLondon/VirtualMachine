#include <cmath>
#include <limits>
#include "instruction.hpp"

Instruction::Instruction(
    uint16_t opcode,
    bool     set_status,
    uint8_t  suffix,
    uint8_t  target,
    uint8_t  register1,
    uint8_t  register2,
    Float    immediate,
    uint8_t  flags
    ):
    opcode{opcode},
    set_status{set_status},
    suffix{suffix},
    target{target},
    register1{register1},
    register2{register2},
    immediate{immediate},
    flags{flags}
{
    
}

bool Instruction::check_flags(uint8_t flag)
{
    return flags & flag;
}

std::string Instruction::to_string()
{
    std::string builder = "";
    if (flags & BITF)
        builder += "B";
    builder += OPCODE_LOOKUP[opcode];
    if (flags & IMMF)
        builder += "I";
    if (set_status)
        builder += "S";
    builder += SUFFIX_LOOKUP[suffix];
    builder += "\t";
    builder += (target >= REG_COUNT ? "F" + std::to_string(target - REG_COUNT)
                                    : "R" + std::to_string(target));
    builder += "\t";
    builder += (register1 >= REG_COUNT ? "F" + std::to_string(register1 - REG_COUNT)
                                       : "R" + std::to_string(register1));
    builder += "\t";
    builder += (register2 >= REG_COUNT ? "F" + std::to_string(register2 - REG_COUNT)
                                       : "R" + std::to_string(register2));
    builder += "\t";
    builder += std::to_string(immediate);

    return builder;
}

void Instruction::execute()
{
    if (!check_suffix())
        return;

    switch (opcode) {
    // r type
    case NOP:  return;
    case ADD:  op_add();  break;
    case SUB:  op_sub();  break;
    case MUL:  op_mul();  break;
    case DIV:  op_div();  break;
    case MOD:  op_mod();  break;
    case AND:  op_and();  break;
    case XOR:  op_xor();  break;
    case OR:   op_or();   break;
    case NOT:  op_not();  break;
    case COMP: op_comp(); break;
    case SHR:  op_shr();  break;
    case SHL:  op_shl();  break;
    case CMP:  op_cmp();  break;
    case SWP:  op_swp();  break;
    case MOV:  op_mov();  break;
    // i type
    case SET:  op_set();  break;
    case CLR:  op_clr();  break;
    case SW:   op_sw();   break;
    case LW:   op_lw();   break;
    case INC:  op_inc();  break;
    case DEC:  op_dec();  break;
    case PUSH: op_push(); break;
    case POP:  op_pop();  break;
    // j type
    case JMP:  op_jmp();  break;
    case CALL: op_call(); break;
    case RET:  op_ret();  break;
    default:
        std::cerr << "Opcode Error: Unexpected opcode '" << opcode << "'. Exiting..." << std::endl;
        std::exit(-1);
    }

    if (!set_status)
        return;
    
    if (check_flags(IMMF))
        mem->set_flags(reg_at(mem, register1) - immediate);
    else
        mem->set_flags(reg_at(mem, register1) - reg_at(mem, register2));
}

bool Instruction::check_suffix()
{
    switch(suffix) {
    case CS:
        return mem->flags.carry;
    case CC:
        return !mem->flags.carry;
    case ZS:
        return mem->flags.zero;
    case ZC:
        return !mem->flags.zero;
    case NS:
        return mem->flags.neg;
    case NC:
        return !mem->flags.neg;
    case EQ:
        return mem->flags.equal;
    case NE:
        return !mem->flags.equal;
    case LT:
        return mem->flags.less_than;
    case GE:
        return !mem->flags.less_than;
    case GT:
        return mem->flags.greater_than;
    case LE:
        return !mem->flags.greater_than;
    case AL:    // always, auto added if user didn't
        return true;
    default:
        std::cerr << "Status Error: Unexpected status '" << set_status << "'. Exiting..." << std::endl;
        std::exit(-1);
    }
    return false;
}

void Instruction::op_add()
{
    if (check_flags(IMMF))
        reg_set(mem, target, reg_at(mem, register1) + immediate);
    else
        reg_set(mem, target, reg_at(mem, register1) + reg_at(mem, register2));
}

void Instruction::op_sub()
{
    if (check_flags(IMMF))
        reg_set(mem, target, reg_at(mem, register1) - immediate);
    else
        reg_set(mem, target, reg_at(mem, register1) - reg_at(mem, register2));
}

void Instruction::op_mul()
{
    if (check_flags(IMMF))
        reg_set(mem, target, reg_at(mem, register1) * immediate);
    else
        reg_set(mem, target, reg_at(mem, register1) * reg_at(mem, register2));
}

void Instruction::op_div()
{
    if (check_flags(IMMF))
        reg_set(mem, target, reg_at(mem, register1) / immediate);
    else
        reg_set(mem, target, reg_at(mem, register1) / reg_at(mem, register2));
}

void Instruction::op_mod()
{
    if (check_flags(IMMF))
        reg_set(mem, target, fmod(reg_at(mem, register1), immediate));
    else
        reg_set(mem, target, fmod(reg_at(mem, register1), reg_at(mem, register2)));
}

void Instruction::op_and()
{
    if (check_flags(IMMF | BITF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) & (Signed)immediate);
    else if (check_flags(BITF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) & (Signed)reg_at(mem, register2));
    else if (check_flags(IMMF))
        reg_set(mem, target, reg_at(mem, register1) && immediate);
    else
        reg_set(mem, target, reg_at(mem, register1) && reg_at(mem, register2));
}

void Instruction::op_xor()
{
    if (check_flags(IMMF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) ^ (Signed)immediate);
    else
        reg_set(mem, target, (Signed)reg_at(mem, register1) ^ (Signed)reg_at(mem, register2));
}

void Instruction::op_or()
{
    if (check_flags(IMMF | BITF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) | (Signed)immediate);
    else if (check_flags(BITF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) | (Signed)reg_at(mem, register2));
    else if (check_flags(IMMF))
        reg_set(mem, target, reg_at(mem, register1) || immediate);
    else
        reg_set(mem, target, reg_at(mem, register1) || reg_at(mem, register2));
}

void Instruction::op_not()
{
    reg_set(mem, target, !reg_at(mem, register1));
}

void Instruction::op_comp()
{
    reg_set(mem, target, !(Signed)reg_at(mem, register1));
}

void Instruction::op_shr()
{
    if (check_flags(IMMF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) >> (Signed)immediate);
    else if (check_flags(BITF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) >> (Signed)reg_at(mem, register2));
    else {
        std::cerr << "Parse Error: Instruction 'shr' missing IMMF or BITF flags. Exiting..." << std::endl;
        std::exit(-1);
    }
}

void Instruction::op_shl()
{
    if (check_flags(IMMF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) << (Signed)immediate);
    else if (check_flags(BITF))
        reg_set(mem, target, (Signed)reg_at(mem, register1) << (Signed)reg_at(mem, register2));
    else {
        std::cerr << "Parse Error: Instruction 'shl' missing IMMF or BITF flags. Exiting..." << std::endl;
        std::exit(-1);
    }
}

void Instruction::op_cmp()
{
    set_status = true;
}

void Instruction::op_swp()
{
    Float temp = reg_at(mem, target);
    reg_set(mem, target, reg_at(mem, register1));
    reg_set(mem, register1, temp);
}

void Instruction::op_mov()
{
    if (check_flags(IMMF))
        reg_set(mem, target, immediate);
    else
        reg_set(mem, target, reg_at(mem, register1));
}

void Instruction::op_set()
{
    if (target >= REG_COUNT)
        mem->fregfile[target - REG_COUNT] = std::numeric_limits<Float>::max();
    else
        mem->iregfile[target] = std::numeric_limits<Signed>::max();
}

void Instruction::op_clr()
{
    reg_set(mem, target, 0);
}

void Instruction::op_sw()
{
    if (target >= REG_COUNT)
        mem->dmem[immediate] = reinterpret_cast<Signed&>(mem->fregfile[target - REG_COUNT]);
    else
        mem->dmem[immediate] = mem->iregfile[target];
}

void Instruction::op_lw()
{
    if (target >= REG_COUNT)
        mem->fregfile[target - REG_COUNT] = reinterpret_cast<Float&>(mem->dmem[immediate]);
    else
        mem->iregfile[target] = mem->dmem[immediate];
}

void Instruction::op_inc()
{
    reg_increase(mem, target, 1);
}

void Instruction::op_dec()
{
    reg_increase(mem, target, -1);
}

void Instruction::op_push()
{
    if (target >= REG_COUNT)
        mem->data_stack.push(reinterpret_cast<Signed&>(mem->fregfile[target - REG_COUNT]));
    else
        mem->data_stack.push(mem->iregfile[target]);
}

void Instruction::op_pop()
{
    if (mem->data_stack.size() <= 0) {
        std::cerr << "Stack Error: Attempted to pop empty stack. Exiting..." << std::endl;
        std::exit(-1);
    }

    if (target >= REG_COUNT)
        mem->fregfile[target - REG_COUNT] = reinterpret_cast<Float&>(mem->data_stack.top());
    else
        mem->iregfile[target] = mem->data_stack.top();
    
    mem->data_stack.pop();
}

void Instruction::op_jmp()
{
    mem->pc_jmp((Signed)(reg_at(mem, target) + immediate));
}

void Instruction::op_call()
{
    mem->call_stack.push(mem->pc());
    mem->pc_jmp((Signed)(reg_at(mem, target) + immediate));
}

void Instruction::op_ret()
{
    if (mem->call_stack.size() <= 0) {
        std::cerr << "Stack Error: Attempted to pop empty stack. Exiting..." << std::endl;
        std::exit(-1);
    }

    mem->pc_jmp(mem->call_stack.top());
    mem->call_stack.pop();
}
