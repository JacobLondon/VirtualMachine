#include <cmath>
#include "instruction.hpp"

Instruction::Instruction(u16 opcode, bool set_status, u8 suffix, u8 target, u8 register1, u8 register2, f64 immediate, u8 flags)
    : opcode{opcode}, set_status{set_status}, suffix{suffix}, target{target}, register1{register1}, register2{register2}, immediate{immediate}, flags{flags}
{

}

bool Instruction::check_flags(u8 flag)
{
    return flags & flag;
}

std::string Instruction::to_string()
{
    std::string builder = "";
    builder += OPCODE_LOOKUP[opcode];
    if (set_status)
        builder += "S";
    builder += SUFFIX_LOOKUP[suffix];
    builder += "\t";
    builder += (target >= REG_COUNT ? "F" + std::to_string(target - REG_COUNT) : "R" + std::to_string(target));
    builder += "\t";
    builder += (register1 >= REG_COUNT ? "F" + std::to_string(register1 - REG_COUNT) : "R" + std::to_string(register1));
    builder += "\t";
    builder += (register2 >= REG_COUNT ? "F" + std::to_string(register2 - REG_COUNT) : "R" + std::to_string(register2));
    builder += "\t";
    builder += std::to_string(immediate);

    return builder;
}

void Instruction::execute(Memory& mem)
{
    if (!check_suffix(mem))
        return;

    switch (opcode) {
    // r type
    case NOP:  return;
    case ADD:  op_add(mem);  break;
    case SUB:  op_sub(mem);  break;
    case MUL:  op_mul(mem);  break;
    case DIV:  op_div(mem);  break;
    case MOD:  op_mod(mem);  break;
    case AND:  op_and(mem);  break;
    case XOR:  op_xor(mem);  break;
    case OR:   op_or(mem);   break;
    case NOT:  op_not(mem);  break;
    case COMP: op_comp(mem); break;
    case SHR:  op_shr(mem);  break;
    case SHL:  op_shl(mem);  break;
    case CMP:  op_cmp(mem);  break;
    case SWP:  op_swp(mem);  break;
    case MOV:  op_mov(mem);  break;
    // i type
    case SET:  op_set(mem);  break;
    case CLR:  op_clr(mem);  break;
    case SW:   op_sw(mem);   break;
    case LW:   op_lw(mem);   break;
    case INC:  op_inc(mem);  break;
    case DEC:  op_dec(mem);  break;
    case PUSH: op_push(mem); break;
    case POP:  op_pop(mem);  break;
    // j type
    case JMP:  op_jmp(mem);  break;
    case CALL: op_call(mem); break;
    case RET:  op_ret(mem);  break;
    default:
        std::cerr << "Opcode Error: Unexpected opcode '" << opcode << "'. Exiting..." << std::endl;
        exit(-1);
    }

    if (!set_status)
        return;
    
    if (check_flags(IMMF))
        mem.set_flags(REG_AT(register1, mem) - immediate);
    else
        mem.set_flags(REG_AT(register1, mem) - REG_AT(register2, mem));
}

bool Instruction::check_suffix(Memory& mem)
{
    switch(suffix) {
    case CS:
        return mem.flags.carry;
    case CC:
        return !mem.flags.carry;
    case ZS:
        return mem.flags.zero;
    case ZC:
        return !mem.flags.zero;
    case NS:
        return mem.flags.neg;
    case NC:
        return !mem.flags.neg;
    case EQ:
        return mem.flags.equal;
    case NE:
        return !mem.flags.equal;
    case LT:
        return mem.flags.less_than;
    case GE:
        return !mem.flags.less_than;
    case GT:
        return mem.flags.greater_than;
    case LE:
        return !mem.flags.greater_than;
    case AL:    // always, auto added if user didn't
        return true;
    default:
        std::cerr << "Status Error: Unexpected status '" << set_status << "'. Exiting..." << std::endl;
        exit(-1);
    }
    return false;
}

void Instruction::op_add(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, REG_AT(register1, mem) + immediate);
    else
        REG_SET(target, mem, REG_AT(register1, mem) + REG_AT(register2, mem));
}

void Instruction::op_sub(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, REG_AT(register1, mem) - immediate);
    else
        REG_SET(target, mem, REG_AT(register1, mem) - REG_AT(register2, mem));
}

void Instruction::op_mul(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, REG_AT(register1, mem) * immediate);
    else
        REG_SET(target, mem, REG_AT(register1, mem) * REG_AT(register2, mem));
}

void Instruction::op_div(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, REG_AT(register1, mem) / immediate);
    else
        REG_SET(target, mem, REG_AT(register1, mem) / REG_AT(register2, mem));
}

void Instruction::op_mod(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, fmod(REG_AT(register1, mem), immediate));
    else
        REG_SET(target, mem, fmod(REG_AT(register1, mem), REG_AT(register2, mem)));
}

void Instruction::op_and(Memory& mem)
{
    if (check_flags(IMMF | BITF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) & (s64)immediate);
    else if (check_flags(BITF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) & (s64)REG_AT(register2, mem));
    else if (check_flags(IMMF))
        REG_SET(target, mem, REG_AT(register1, mem) && immediate);
    else
        REG_SET(target, mem, REG_AT(register1, mem) && REG_AT(register2, mem));
}

void Instruction::op_xor(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) ^ (s64)immediate);
    else
        REG_SET(target, mem, (s64)REG_AT(register1, mem) ^ (s64)REG_AT(register2, mem));
}

void Instruction::op_or(Memory& mem)
{
    if (check_flags(IMMF | BITF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) | (s64)immediate);
    else if (check_flags(BITF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) | (s64)REG_AT(register2, mem));
    else if (check_flags(IMMF))
        REG_SET(target, mem, REG_AT(register1, mem) || immediate);
    else
        REG_SET(target, mem, REG_AT(register1, mem) || REG_AT(register2, mem));
}

void Instruction::op_not(Memory& mem)
{
    REG_SET(target, mem, !REG_AT(register1, mem));
}

void Instruction::op_comp(Memory& mem)
{
    REG_SET(target, mem, ~(s64)REG_AT(register1, mem));
}

void Instruction::op_shr(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) >> (s64)immediate);
    else if (check_flags(BITF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) >> (s64)REG_AT(register2, mem));
    else {
        std::cerr << "Parse Error: Instruction 'shr' missing IMMF or BITF flags. Exiting..." << std::endl;
        exit(-1);
    }
}

void Instruction::op_shl(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) << (s64)immediate);
    else if (check_flags(BITF))
        REG_SET(target, mem, (s64)REG_AT(register1, mem) << (s64)REG_AT(register2, mem));
    else {
        std::cerr << "Parse Error: Instruction 'shl' missing IMMF or BITF flags. Exiting..." << std::endl;
        exit(-1);
    }
}

void Instruction::op_cmp(Memory& mem)
{
    set_status = true;
}

void Instruction::op_swp(Memory& mem)
{
    f64 temp = REG_AT(target, mem);
    REG_SET(target, mem, REG_AT(register1, mem));
    REG_SET(register1, mem, temp);
}

void Instruction::op_mov(Memory& mem)
{
    if (check_flags(IMMF))
        REG_SET(target, mem, immediate);
    else
        REG_SET(target, mem, REG_AT(register1, mem));
}

void Instruction::op_set(Memory& mem)
{
    if (target >= REG_COUNT)
        mem.fregfile[target - REG_COUNT] = std::numeric_limits<f64>::max();
    else
        mem.iregfile[target] = std::numeric_limits<s64>::max();
}

void Instruction::op_clr(Memory& mem)
{
    REG_SET(target, mem, 0);
}

void Instruction::op_sw(Memory& mem)
{
    if (target >= REG_COUNT)
        mem.dmem[immediate] = reinterpret_cast<s64&>(mem.fregfile[target - REG_COUNT]);
    else
        mem.dmem[immediate] = mem.iregfile[target];
}

void Instruction::op_lw(Memory& mem)
{
    if (target >= REG_COUNT)
        mem.fregfile[target - REG_COUNT] = reinterpret_cast<f64&>(mem.dmem[immediate]);
    else
        mem.iregfile[target] = mem.dmem[immediate];
}

void Instruction::op_inc(Memory & mem)
{
    reg_increase(mem, target, 1);
}

void Instruction::op_dec(Memory & mem)
{
    reg_increase(mem, target, -1);
}

void Instruction::op_push(Memory & mem)
{
    if (target >= REG_COUNT)
        mem.data_stack.push(reinterpret_cast<s64&>(mem.fregfile[target - REG_COUNT]));
    else
        mem.data_stack.push(mem.iregfile[target]);
}

void Instruction::op_pop(Memory & mem)
{
    if (mem.data_stack.size() <= 0) {
        std::cerr << "Stack Error: Attempted to pop empty stack. Exiting..." << std::endl;
        exit(-1);
    }

    if (target >= REG_COUNT)
        mem.fregfile[target - REG_COUNT] = reinterpret_cast<f64&>(mem.data_stack.top());
    else
        mem.iregfile[target] = mem.data_stack.top();
    
    mem.data_stack.pop();
}

void Instruction::op_jmp(Memory& mem)
{
    mem.pc_jmp((s64)(REG_AT(target, mem) + immediate));
}

void Instruction::op_call(Memory& mem)
{
    mem.call_stack.push(mem.pc());
    mem.pc_jmp((s64)(REG_AT(target, mem) + immediate));
}

void Instruction::op_ret(Memory& mem)
{
    if (mem.call_stack.size() <= 0) {
        std::cerr << "Stack Error: Attempted to pop empty stack. Exiting..." << std::endl;
        exit(-1);
    }

    mem.pc_jmp(mem.call_stack.top());
    mem.call_stack.pop();
}
