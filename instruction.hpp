#pragma once
#include "types.hpp"

class instruction {
public:
    
    /**
     * j type
     */

    // b 0x1000 disallowed -> use b 0x1000[0]
    // b r15 disallowed    -> use b r15[0]

    // b r15[0x1000] or b 0x1000[r15]
    instruction(u16 opcode, u8 suffix, u8 register1, u64 immediate);
    // b r14[r15]
    instruction(u16 opcode, u8 suffix, u8 register1, u8 register2);

    /**
     * i type
     */

    // sw $r14 $r15[10] or lw $r14 $r15[10]
    instruction(u16 opcode, u8 suffix, u8 target, u8 register1, u64 immediate, bool floating);
    // sw $r13 $r14[$r15] or lw $r13 $r14[$r15]
    instruction(u16 opcode, u8 suffix, u8 target, u8 register1, u8 register2, bool floating);
    

    /**
     * r type
     */

    instruction(u16 opcode, bool status, u8 suffix, u8 target, u8 register1, u8 register2, bool floating, bool imm);
    std::string to_string();
    inline bool check_flags(u8 flag);

    u16 opcode = 0;

    const u8 BIT = 0x01;
    const u8 FLOAT = 0x02;
    const u8 IMM = 0x04;
    bool status = false;
    u8 flags = 0;

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
