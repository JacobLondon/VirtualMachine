#include <iostream>
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
        //std::cout << mem.imem[mem.pc()].to_string() << std::endl;
        mem.imem[mem.pc()].execute(mem);
        //std::cout << mem.dump() << std::endl;
        //std::cin.get();
    }
    done = true;
}
