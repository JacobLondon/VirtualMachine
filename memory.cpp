//#include "parser.hpp"
#include <limits>
#include <sstream>
#include "memory.hpp"

Memory::Memory(u64 dmem_size)
{
    dmem.reserve(dmem_size);
}

std::string Memory::to_string()
{
    std::stringstream builder;
    for (u64 i = 0; i < 50; i++) builder << "-";
    builder << "Integer Registers\t\t\tFloating Point Registers";
    for (u64 i = 0; i < iregfile.size(); i++) builder << std::hex << iregfile[i] << "\t" << fregfile[i] << "\n";
    builder << "Flags: " << flags << "\n";
    return builder.str();
}

inline s64 Memory::zero()
{
    return iregfile[0];
}

inline s64 Memory::pc()
{
    return iregfile[iregfile.size() - 1];
}

inline void Memory::pc_rst()
{
    iregfile[iregfile.size() - 1] = 0;
}

inline void Memory::pc_inc()
{
    iregfile[iregfile.size() - 1]++;
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
