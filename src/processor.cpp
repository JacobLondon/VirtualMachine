#include "processor.hpp"
#include "display.hpp"

Processor::Processor(Unsigned data_size)
    : mem(data_size)
{}

void Processor::execute()
{
    Display d{&mem};

    done = false;
    for (mem.pc_rst(); mem.pc() < mem.imem.size(); mem.pc_inc()) {
        mem.imem[mem.pc()].execute();
        d.update();
    }
    
    done = true;
}
