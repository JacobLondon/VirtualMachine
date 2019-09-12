#pragma once
#include "types.hpp"

class instruction {
public:
    instruction();
    u8 opcode = 0;
};

class jtype : public instruction {
public:
    jtype(u8 opcode, u64 address);
    u8 opcode = 0;
    u64 address = 0;
};

template<class T>
class itype : public instruction {
public:
    itype(u8 opcode, u8 suffix, u8 target, T immediate);
    u8 opcode = 0;
    u8 suffix = 0;
    u8 target = 0;
    T immediate = 0;
};

class rtype : public instruction {
public:
    rtype(u8 opcode, bool status, u8 suffix, u8 target, u8 register1, u8 register2);
    u8 opcode = 0;
    bool status = false;
    u8 suffix = 0;
    u8 target = 0;
    u8 register1 = 0;
    u8 register2 = 0;
};
