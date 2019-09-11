#include "instruction.h"

jtype::jtype(u8 opcode, u8 status, u64 address)
    : opcode(opcode), status(status), address(address)
{

}

itype::itype(u8 opcode, u8 status, u8 suffix, u8 target, u64 immediate)
    : opcode(opcode), status(status), suffix(suffix), target(target), immediate(immediate)
{

}

rtype::rtype(u8 opcode, u8 status, u8 suffix, u8 target, u8 register1, u8 register2)
    : opcode(opcode), status(status), suffix(suffix), target(target), register1(register1), register2(register2)
{

}
