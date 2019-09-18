#include <iostream>
#include "processor.hpp"

int main()
{
    Processor p(1000);

    p.mem.imem.push_back(Instruction(MOV, false, AL, RegisterRef(F1, FLOATF), RegisterRef(),         RegisterRef(),           255.6, IMMF));
    p.mem.imem.push_back(Instruction(MOV, false, AL, RegisterRef(R1, INTF),   RegisterRef(),         RegisterRef(),           10,    IMMF));
    p.mem.imem.push_back(Instruction(ADD, false, AL, RegisterRef(R2, INTF),   RegisterRef(R1, INTF), RegisterRef(F1, FLOATF), 0,     NOF ));

    p.execute();
    std::cout << p.mem.dump() << std::endl;
    return 0;
}
