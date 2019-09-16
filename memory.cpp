//#include "parser.hpp"
#include <limits>
#include "memory.hpp"

Memory::Memory(u64 dmem_size)
{
    dmem.reserve(dmem_size);
}

inline bool Memory::status_v()
{
    return flags & V_FLAG;
}

inline bool Memory::status_c()
{
    return flags & C_FLAG;
}

inline bool Memory::status_z()
{
    return flags & Z_FLAG;
}

inline bool Memory::status_n()
{
    return flags & N_FLAG;
}
