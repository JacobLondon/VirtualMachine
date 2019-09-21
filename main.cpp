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
    
    p.mem.imem.push_back(Instruction(MOV, false, AL, RegisterRef(R1, INTF),   RegisterRef(),           RegisterRef(),         2, IMMF));
    p.mem.imem.push_back(Instruction(DEC, false, AL, RegisterRef(R1, INTF),   RegisterRef(),           RegisterRef(),        0, NOF));
    p.mem.imem.push_back(Instruction(CMP, false, AL, RegisterRef(),   RegisterRef(R1, INTF),           RegisterRef(ZERO, INTF),        0, NOF));
    p.mem.imem.push_back(Instruction(JMP, false, ZC, RegisterRef(ZERO, INTF), RegisterRef(),           RegisterRef(),         0, IMMF));

    p.execute();
    std::cout << p.mem.dump() << std::endl;
    return 0;
}
