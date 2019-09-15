#include "instruction.hpp"

Instruction::Instruction(u16 opcode, bool status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, s64 immediate)
    : opcode{opcode}, status{status}, suffix{suffix}, target{target}, register1{register1}, register2{register2}, immediate{immediate}
{
    
}

Instruction::Instruction(u16 opcode, bool status, u8 suffix, RegisterRef target, RegisterRef register1, RegisterRef register2, f64 immediate)
    : opcode{opcode}, status{status}, suffix{suffix}, target{target}, register1{register1}, register2{register2}, immediate{immediate}
{
    
}

std::string Instruction::to_string()
{
    std::string builder = "";
    builder += "opcode: " + std::to_string(opcode) + "\n";
    builder += "suffix: " + std::to_string(suffix) + "\n";
    builder += "target: " + std::to_string(target.address) + "\n";
    builder += "register1: " + std::to_string(register1.address) + "\n";
    builder += "register2: " + std::to_string(register2.address) + "\n";
    if (check_flags(IMM)) {
        builder += "Immediate: ";
        if (check_flags(FLOAT))
            builder += std::to_string(immediate.floating);
        else
            builder += std::to_string(immediate.integer);
    }
    return builder;
}

inline bool Instruction::check_flags(u8 flag)
{
    return ((flags & flag) | flag);
}

void Instruction::execute(Memory& memory)
{
    if (!check_suffix(memory))
        return;

    switch (opcode) {
    // r type
    case ADD:  op_add(memory);  break;
    case SUB:  op_sub(memory);  break;
    case MUL:  op_mul(memory);  break;
    case DIV:  op_div(memory);  break;
    case MOD:  op_mod(memory);  break;
    case AND:  op_and(memory);  break;
    case XOR:  op_xor(memory);  break;
    case OR:   op_or(memory);   break;
    case NOT:  op_not(memory);  break;
    case COMP: op_comp(memory); break;
    case SHR:  op_shr(memory);  break;
    case SHL:  op_shl(memory);  break;
    case CMP:  op_cmp(memory);  break;
    case SWP:  op_swp(memory);  break;
    case MOV:  op_mov(memory);  break;
    // i type
    case SET:  op_set(memory);  break;
    case CLR:  op_clr(memory);  break;
    case SW:   op_sw(memory);   break;
    case LW:   op_lw(memory);   break;
    // j type
    case B:    op_b(memory);    break;
    case CALL: op_call(memory); break;
    case RET:  op_ret(memory);  break;
    default:
        std::cerr << "Error - Unexpected opcode: " << opcode << std::endl;
        exit(-1);
    }

    if (status)
        memory.set_flags(REG_1(this, memory) - REG_2(this, memory));
}

bool Instruction::check_suffix(Memory& memory)
{
    switch(status) {
    case EQ:    // z set
        return memory.status_z();
    case NE:    // z clear
        return !memory.status_z();
    case CS:    // c set
    case HS:
        return memory.status_c();
    case CC:    // c clear
    case LO:
        return !memory.status_c();
    case MI:    // n set
        return memory.status_n();
    case PL:    // n clear
        return !memory.status_n();
    case VS:    // v set
        return memory.status_v();
    case VC:    // v clear
        return !memory.status_v();
    case HI:    // v set and z clear
        return memory.status_v() && !memory.status_z();
    case LS:    // c clear and z set
        return !memory.status_c() && memory.status_z();
    case GE:    // n == v
        return memory.status_n() == memory.status_v();
    case LT:    // n != v
        return memory.status_n() != memory.status_v();
    case GT:    // z clear, n == v
        return !memory.status_z() && (memory.status_n() == memory.status_v());
    case LE:    // z set, n != v
        return memory.status_z() && (memory.status_n() != memory.status_v());
    case AL:    // always, auto added if user didn't
        return true;
    default:
        std::cerr << "Error - Unexpected status: " << status << std::endl;
        exit(-1);
    }
    return false;
}

inline void Instruction::set_target(s64 value, Memory& mem)
{
    mem.iregfile[target.address] = value;
}

inline void Instruction::set_target(f64 value, Memory& mem)
{
    mem.fregfile[target.address] = value;
}

inline void Instruction::set_target(bool value, Memory& mem)
{
    mem.fregfile[target.address] = value;
}

inline void Instruction::op_add(Memory& mem)
{
    if (check_flags(IMM))
        set_target(REG_1(this, mem) + IMMEDIATE(this), mem);
    else
        set_target(REG_1(this, mem) + REG_2(this, mem), mem);
}
inline void Instruction::op_sub(Memory& mem)
{
    if (check_flags(IMM))
        set_target(REG_1(this, mem) - IMMEDIATE(this), mem);
    else
        set_target(REG_1(this, mem) - REG_2(this, mem), mem);
}
inline void Instruction::op_mul(Memory& mem)
{
    if (check_flags(IMM))
        set_target(REG_1(this, mem) * IMMEDIATE(this), mem);
    else
        set_target(REG_1(this, mem) * REG_2(this, mem), mem);
}
inline void Instruction::op_div(Memory& mem)
{
    if (check_flags(IMM))
        set_target(REG_1(this, mem) / IMMEDIATE(this), mem);
    else
        set_target(REG_1(this, mem) / REG_2(this, mem), mem);
}
inline void Instruction::op_mod(Memory& mem)
{
    if (check_flags(IMM))
        set_target(fmod(REG_1(this, mem), IMMEDIATE(this)), mem);
    else
        set_target(fmod(REG_1(this, mem), REG_2(this, mem)), mem);
}
inline void Instruction::op_and(Memory& mem)
{
    if (check_flags(IMM | BIT))
        set_target((s64)REG_1(this, mem) & (s64)IMMEDIATE(this), mem);
    else if (check_flags(BIT))
        set_target((s64)REG_1(this, mem) & (s64)REG_2(this, mem), mem);
    if (check_flags(IMM))
        this->set_target(REG_1(this, mem) && IMMEDIATE(this), mem);
    else
        set_target(REG_1(this, mem) && REG_2(this, mem), mem);
}
inline void Instruction::op_xor(Memory& mem)
{
    if (check_flags(IMM))
        set_target((s64)REG_1(this, mem) ^ (s64)IMMEDIATE(this), mem);
    else
        set_target((s64)REG_1(this, mem) ^ (s64)REG_2(this, mem), mem);
}
inline void Instruction::op_or(Memory& mem)
{
    if (check_flags(IMM | BIT))
        set_target((s64)REG_1(this, mem) | (s64)IMMEDIATE(this), mem);
    else if (check_flags(BIT))
        set_target((s64)REG_1(this, mem) | (s64)REG_2(this, mem), mem);
    if (check_flags(IMM))
        this->set_target(REG_1(this, mem) || IMMEDIATE(this), mem);
    else
        set_target(REG_1(this, mem) || REG_2(this, mem), mem);
}
inline void Instruction::op_not(Memory& mem)
{
    set_target(!REG_1(this, mem), mem);
}
inline void Instruction::op_comp(Memory& mem)
{
    set_target(~(s64)REG_1(this, mem), mem);
}
inline void Instruction::op_shr(Memory& mem)
{
    if (check_flags(IMM))
        set_target((s64)REG_1(this, mem) >> (s64)IMMEDIATE(this), mem);
    else
        set_target((s64)REG_1(this, mem) >> (s64)REG_2(this, mem), mem);
}
inline void Instruction::op_shl(Memory& mem)
{
    if (check_flags(IMM))
        set_target((s64)REG_1(this, mem) << (s64)IMMEDIATE(this), mem);
    else
        set_target((s64)REG_1(this, mem) << (s64)REG_2(this, mem), mem);
}
inline void Instruction::op_cmp(Memory& mem)
{
    status = true;
}
inline void Instruction::op_swp(Memory& mem)
{
    if (target.flags == FLOAT && register1.flags == FLOAT)
    // TODO
    std::swap(REG_TARGET(this, mem), REG_1(this, mem));
}
inline void Instruction::op_mov(Memory& mem);
inline void Instruction::op_set(Memory& mem);
inline void Instruction::op_clr(Memory& mem);
inline void Instruction::op_sw(Memory& mem);
inline void Instruction::op_lw(Memory& mem);
inline void Instruction::op_b(Memory& mem);
inline void Instruction::op_call(Memory& mem);
inline void Instruction::op_ret(Memory& mem);