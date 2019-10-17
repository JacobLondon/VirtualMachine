#include <iostream>
#include <tuple>

#include "processor.hpp"
#include "parser.hpp"

int main()
{
    Processor p(1000);
    Parser parse("ex.s");
    std::tie(p.mem.imem, std::ignore) = parse.parse();
    
    p.mem.insert(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));
    p.mem.insert(Instruction(MOV, false, AL, R1,   ZERO, ZERO, 2, IMMF));
    p.mem.insert(Instruction(DEC, false, AL, R1,   ZERO, ZERO, 0, NOF));
    p.mem.insert(Instruction(CMP, false, AL, ZERO,   R1, ZERO, 0, NOF));
    p.mem.insert(Instruction(JMP, false, ZC, ZERO, ZERO, ZERO, 1, IMMF));

    for (int i = 0; i < 50; i++)
        p.mem.insert(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));

    p.execute();
    return 0;
}
