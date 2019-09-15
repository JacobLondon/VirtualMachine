#include "parser.hpp"
#include "memory.hpp"

Memory::Memory(u64 dmem_size)
{
    dmem.reserve(dmem_size);
}

void Memory::set_flags(f64 result)
{
    flags = result;
}

void Memory::set_flags(s64 result)
{
    flags = result;
}

inline bool Memory::status_v()
{
    return flags & VFLAG;
}

inline bool Memory::status_c()
{
    return flags & CFLAG;
}

inline bool Memory::status_z()
{
    return flags & ZFLAG;
}

inline bool Memory::status_n()
{
    return flags & NFLAG;
}
