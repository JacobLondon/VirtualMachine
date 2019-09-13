#include "instruction.hpp"

instruction::instruction(u8 opcode, u8 suffix, u64 address)
    : opcode{opcode}, suffix{suffix}, immediate{address}
{
    status = false;
    target = 0;
    register1 = 0;
    register2 = 0;
}

instruction::instruction(u8 opcode, u8 suffix, u8 target, u8 register1, s64 immediate)
{
    
}

instruction::instruction(u8 opcode, u8 suffix, u8 target, u8 register1, f64 immediate)
{

}

instruction::instruction(u8 opcode, bool status, u8 suffix, u8 target, u8 register1, u8 register2)
{

}
