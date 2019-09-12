#include "instruction.hpp"

rtype::rtype(u8 opcode, bool status, u8 suffix, u8 target, u8 register1, u8 register2)
    : opcode(opcode), status(status), suffix(suffix), target(target), register1(register1), register2(register2)
{

}

template<class T>
itype<T>::itype(u8 opcode, u8 suffix, u8 target, T immediate)
    : opcode(opcode), suffix(suffix), target(target), immediate(immediate)
{

}

jtype::jtype(u8 opcode, u64 address)
    : opcode(opcode), address(address)
{

}
