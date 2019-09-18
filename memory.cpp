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

s64 Memory::zero()
{
    return iregfile[0];
}

s64 Memory::pc()
{
    return iregfile[iregfile.size() - 1];
}

void Memory::pc_rst()
{
    iregfile[iregfile.size() - 1] = 0;
}

void Memory::pc_jmp(s64 address)
{
    iregfile[iregfile.size() - 1] = address;
}

void Memory::pc_inc()
{
    iregfile[iregfile.size() - 1]++;
}

/**
 * statuses
 */

bool Memory::status_v()
{
    return flags & V_FLAG;
}

bool Memory::status_c()
{
    return flags & C_FLAG;
}

bool Memory::status_z()
{
    return flags & Z_FLAG;
}

bool Memory::status_n()
{
    return flags & N_FLAG;
}
