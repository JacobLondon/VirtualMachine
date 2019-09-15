#include "processor.hpp"

Processor::Processor(u64 data_size)
    : mem(data_size)
{
    // pass
}

void Processor::execute(std::vector<Instruction> instructions)
{
    done = false;
    mem.imem = instructions;
    for (mem.pc = 0; mem.pc < mem.imem.size(); mem.pc++) {
        instructions[mem.pc].execute(mem);
    }
    done = true;
}
