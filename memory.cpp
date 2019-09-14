#include "parser.hpp"
#include "memory.hpp"

memory::memory(u64 dmem_size)
{
    dmem.reserve(dmem_size);
}

inline bool memory::status_v()
{
    return flags & VFLAG;
}

inline bool memory::status_c()
{
    return flags & CFLAG;
}

inline bool memory::status_z()
{
    return flags & ZFLAG;
}

inline bool memory::status_n()
{
    return flags & NFLAG;
}

bool memory::suffix(instruction inst)
{
    switch(inst.status) {
    case EQ:    // z set
        return status_z();
    case NE:    // z clear
        return !status_z();
    case CS:    // c set
    case HS:
        return status_c();
    case CC:    // c clear
    case LO:
        return !status_c();
    case MI:    // n set
        return status_n();
    case PL:    // n clear
        return !status_n();
    case VS:    // v set
        return status_v();
    case VC:    // v clear
        return !status_v();
    case HI:    // v set and z clear
        return status_v() && !status_z();
    case LS:    // c clear and z set
        return !status_c() && status_z();
    case GE:    // n == v
        return status_n() == status_v();
    case LT:    // n != v
        return status_n() != status_v();
    case GT:    // z clear, n == v
        return !status_z() && status_n() == status_v();
    case LE:    // z set, n != v
        return status_z() && status_n() != status_v();
    case AL:    // always, auto added if user didn't
        return true;
    default:
        std::cerr << "Error - Unexpected status: " << inst.status << std::endl;
        exit(-1);
    }
    return false;
}

void memory::set_flags(s64 result)
{
    flags = 0;
    // TODO: VFLAG

    if ((result >> 63) & 1)
        flags &= CFLAG;
    
    if (result == 0)
        flags &= ZFLAG;
    
    if (result < 0)
        flags &= NFLAG;
}
