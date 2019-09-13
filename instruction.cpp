#include "instruction.hpp"

instruction::instruction(u16 opcode, u8 suffix, u64 address)
    : opcode{opcode}, suffix{suffix}, immediate{address}
{
    status = false;
    target = 0;
    register1 = 0;
    register2 = 0;
}

instruction::instruction(u16 opcode, u8 suffix, u8 target, u8 register1, s64 immediate)
    : opcode{opcode}, suffix{suffix}, target{target}, register1{register1}, immediate{immediate}
{
    status = false;
    register2 = 0;
}

instruction::instruction(u16 opcode, u8 suffix, u8 target, u8 register1, f64 immediate)
    : opcode{opcode}, suffix{suffix}, target{target}, register1{register1}, immediate{immediate}
{
    status = false;
    register2 = 0;
}

instruction::instruction(u16 opcode, bool status, u8 suffix, u8 target, u8 register1, u8 register2)
    : opcode{opcode}, status{status}, suffix{suffix}, target{target}, register1{register1}, register2{register2}
{
    immediate = {0}; // doesn't matter
}
