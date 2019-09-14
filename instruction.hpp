#pragma once
#include "types.hpp"

class instruction {
public:
    // j type
    instruction(u16 opcode, u8 suffix, u8 target, u8 register1, u64 immediate);
    // itype
    instruction(u16 opcode, u8 suffix, u8 target, u8 register1, s64 immediate, bool floating);
    instruction(u16 opcode, u8 suffix, u8 target, u8 register1, f64 immediate, bool floating);
    // r type
    instruction(u16 opcode, bool status, u8 suffix, u8 target, u8 register1, u8 register2, bool floating, bool imm);
    std::string to_string();

    u16 opcode = 0;
    bool bitwise = false;
    bool floating = false;
    bool imm = false;
    bool status = false;
    u8 suffix = 0;
    u8 target = 0;
    u8 register1 = 0;
    u8 register2 = 0;
    union _immediate {
        f64 floating;
        s64 integer;
        u64 address;
    } immediate;
};
