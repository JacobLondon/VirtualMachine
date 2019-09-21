#include <iostream>
#include "processor.hpp"

int main()
{
    Processor p(1000);
    /*
    p.mem.imem.push_back(Instruction(MOV, false, AL, RegisterRef(F1, FLOATF), RegisterRef(),         RegisterRef(),           255.6, IMMF));
    p.mem.imem.push_back(Instruction(MOV, false, AL, RegisterRef(R1, INTF),   RegisterRef(),         RegisterRef(),           10,    IMMF));
    p.mem.imem.push_back(Instruction(CMP, false, AL, RegisterRef(R2, INTF),   RegisterRef(R1, INTF), RegisterRef(F1, FLOATF), 0,     NOF ));
    p.mem.imem.push_back(Instruction(ADD, false, PL, RegisterRef(R2, INTF),   RegisterRef(R1, INTF), RegisterRef(F1, FLOATF), 0,     NOF ));
    */
    
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));

    p.mem.imem.push_back(Instruction(MOV, false, AL, R1,   ZERO, ZERO, 2, IMMF));
    p.mem.imem.push_back(Instruction(DEC, false, AL, R1,   ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(CMP, false, AL, ZERO,   R1, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(JMP, false, ZC, ZERO, ZERO, ZERO, 1, IMMF));

    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.imem.push_back(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));

    p.execute();
    return 0;
}
