#include "processor.hpp"

processor::processor(u64 data_size)
    : mem(data_size)
{
    
}

void processor::execute(std::vector<instruction> instructions)
{
    mem.imem = instructions;
}
