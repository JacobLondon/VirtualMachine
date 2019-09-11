#include "memory.h"

memory::memory()
{
    // pass
}

memory::memory(u64 inst_size, u64 data_size, u64 reg_file_size)
{
    register_file.reserve(reg_file_size);
    instruction_memory.reserve(inst_size);
    data_memory.reserve(data_size);
}
