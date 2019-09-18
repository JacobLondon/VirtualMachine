#include <limits>
#include <cmath>
#include "instruction.hpp"

RegisterRef::RegisterRef()
    : address{0}, flags{0}
{
    // pass
}

RegisterRef::RegisterRef(u8 address, u8 flags)
    : address{address}, flags{flags}
{
    // pass
}
bool RegisterRef::check_flags(u8 flag)
{
    return flags & flag;
}

Instruction::Instruction(u16 opcode, bool set_status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, f64 immediate, u8 flags)
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
    builder += "opcode: " + std::to_string(opcode) + "\n";
    builder += "suffix: " + std::to_string(suffix) + "\n";
    builder += "target: " + std::to_string(target.address) + "\n";
    builder += "register1: " + std::to_string(register1.address) + "\n";
    builder += "register2: " + std::to_string(register2.address) + "\n";
    builder += "Immediate: " + std::to_string(immediate) + "\n";

    return builder;
}

void Instruction::execute(Memory& mem)
{
    if (!check_suffix(mem))
        return;

    switch (opcode) {
    // r type
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
    // j type
    case B:    op_b(mem);    break;
    case CALL: op_call(mem); break;
    case RET:  op_ret(mem);  break;
    default:
        std::cerr << "Opcode Error: Unexpected opcode '" << opcode << "'. Exiting..." << std::endl;
        exit(-1);
    }

    if (!set_status)
        return;
    
    if (check_flags(IMMF))
        MEM_SET_FLAGS(mem, target, REG_AT(register1, mem), immediate);
    else
        MEM_SET_FLAGS(mem, target, REG_AT(register1, mem), REG_AT(register2, mem));
}

bool Instruction::check_suffix(Memory& mem)
{
    switch(suffix) {
    case EQ:    // z set
        return mem.status_z();
    case NE:    // z clear
        return !mem.status_z();
    case CS:    // c set
    case HS:
        return mem.status_c();
    case CC:    // c clear
    case LO:
        return !mem.status_c();
    case MI:    // n set
        return mem.status_n();
    case PL:    // n clear
        return !mem.status_n();
    case VS:    // v set
        return mem.status_v();
    case VC:    // v clear
        return !mem.status_v();
    case HI:    // v set and z clear
        return mem.status_v() && !mem.status_z();
    case LS:    // c clear and z set
        return !mem.status_c() && mem.status_z();
    case GE:    // n == v
        return mem.status_n() == mem.status_v();
    case LT:    // n != v
        return mem.status_n() != mem.status_v();
    case GT:    // z clear, n == v
        return !mem.status_z() && (mem.status_n() == mem.status_v());
    case LE:    // z set, n != v
        return mem.status_z() && (mem.status_n() != mem.status_v());
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
    if (check_flags(IMMF)) {
        std::cout << "reg1: " << REG_AT(register1, mem) << "imm: " << immediate << std::endl;
        s64 value = REG_AT(register1, mem) + immediate;
        REG_SET(target, mem, value);
    }
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
    if (target.check_flags(FLOATF))
        mem.fregfile[target.address] = std::numeric_limits<f64>::max();
    else
        mem.iregfile[target.address] = std::numeric_limits<s64>::max();
}

void Instruction::op_clr(Memory& mem)
{
    REG_SET(target, mem, 0);
}

void Instruction::op_sw(Memory& mem)
{
    if (target.check_flags(FLOATF))
        mem.dmem[immediate] = reinterpret_cast<s64&>(mem.fregfile[target.address]);
    else
        mem.dmem[immediate] = mem.fregfile[target.address];
}

void Instruction::op_lw(Memory& mem)
{
    if (target.check_flags(FLOATF))
        mem.fregfile[target.address] = reinterpret_cast<f64&>(mem.dmem[immediate]);
    else
        mem.iregfile[target.address] = mem.dmem[immediate];
}

void Instruction::op_b(Memory& mem)
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
