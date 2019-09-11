#pragma once
#include "types.h"

class instruction {
public:
    instruction();
    u8 opcode;
    u8 status;
};

class jtype : instruction {
public:
    jtype(u8 opcode, u8 status, u64 address);
    u8 opcode;
    u8 status;
    u64 address;
};

class itype : instruction {
public:
    itype(u8 opcode, u8 status, u8 suffix, u8 target, u64 immediate);
    u8 opcode = 0;
    u8 status = 0;
    u8 suffix = 0;
    u8 target = 0;
    u64 immediate = 0;
};

class rtype : instruction {
public:
    rtype(u8 opcode, u8 status, u8 suffix, u8 target, u8 register1, u8 register2);
    u8 opcode = 0;
    u8 status = 0;
    u8 suffix = 0;
    u8 target = 0;
    u8 register1 = 0;
    u8 register2 = 0;
};