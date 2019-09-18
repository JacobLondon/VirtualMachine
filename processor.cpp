#include "processor.hpp"

Processor::Processor(u64 data_size)
    : mem(data_size)
{
    // pass
}

void Processor::execute()
{
    done = false;
    for (mem.pc_rst(); mem.pc() < mem.imem.size(); mem.pc_inc()) {
        mem.imem[mem.pc()].execute(mem);
    }
    done = true;
}
