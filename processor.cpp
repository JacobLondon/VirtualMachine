#include <iostream>
#include "processor.hpp"
#include "display.hpp"

Processor::Processor(u64 data_size)
    : mem(data_size)
{
    // pass
}

void Processor::execute()
{
    Display d{};
    d.startup();

    done = false;
    for (mem.pc_rst(); mem.pc() < mem.imem.size(); mem.pc_inc()) {
        mem.imem[mem.pc()].execute(mem);
        d.update(mem);
    }
    
    done = true;
}
