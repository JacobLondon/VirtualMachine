#include <limits>
#include "memory.hpp"

/**
 * Memory
 */

Memory::Memory(u64 dmem_size)
    : iregfile(REG_COUNT, 0), fregfile(REG_COUNT, 0.0)
{
    dmem.reserve(dmem_size);
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

void Memory::clear_flags()
{
    flags.carry        = false;
    flags.zero         = false;
    flags.neg          = false;
    flags.equal        = false;
    flags.less_than    = false;
    flags.greater_than = false;
    flags.always       = true;
}

void Memory::set_flags(f64 result)
{
    clear_flags();

    if (result < 0)
        flags.carry = true;
    if (result == 0)
        flags.zero = true;
    if (result < 0)
        flags.neg = true;
    if (result == 0)
        flags.equal = true;
    if (result < 0)
        flags.less_than = true;
    if (result > 0)
        flags.greater_than = true;
}
