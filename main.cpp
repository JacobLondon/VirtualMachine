#include <iostream>
#include <tuple>

#include "processor.hpp"
#include "parser.hpp"

int main()
{
    Processor p(1000);
    Parser parse("ex.s");
    std::tie(p.mem.imem, std::ignore) = parse.parse();

    for (int i = 0; i < 50; i++)
        p.mem.insert(Instruction(NOP, false, AL, ZERO, ZERO, ZERO, 0, NOF));

    p.execute();
    return 0;
}
