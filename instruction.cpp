#include "instruction.hpp"

instruction::instruction(u16 opcode, u8 suffix, u8 target, u8 register1, u64 immediate)
    : opcode{opcode}, suffix{suffix}, immediate{immediate}
{
    status = false;
    target = 0;
    register1 = 0;
    register2 = 0;
}

instruction::instruction(u16 opcode, u8 suffix, u8 target, u8 register1, s64 immediate, bool floating)
    : opcode{opcode}, suffix{suffix}, target{target}, register1{register1}, immediate{immediate}
{
    status = false;
    register2 = 0;
}

instruction::instruction(u16 opcode, u8 suffix, u8 target, u8 register1, f64 immediate, bool floating)
    : opcode{opcode}, suffix{suffix}, target{target}, register1{register1}, immediate{immediate}
{
    status = false;
    register2 = 0;
}

instruction::instruction(u16 opcode, bool status, u8 suffix, u8 target, u8 register1, u8 register2, bool floating, bool imm)
    : opcode{opcode}, status{status}, suffix{suffix}, target{target}, register1{register1}, register2{register2}
{
    immediate = {0}; // doesn't matter
}

std::string instruction::to_string()
{
    std::string builder = "";
    builder += "opcode: " + std::to_string(opcode) + "\n";
    builder += "suffix: " + std::to_string(suffix) + "\n";
    builder += "target: " + std::to_string(target) + "\n";
    builder += "register1: " + std::to_string(register1) + "\n";
    builder += "register2: " + std::to_string(register2) + "\n";
    if (imm) {
        builder += "Immediate: ";
        if (floating)
            builder += std::to_string(immediate.floating);
        else
            builder += std::to_string(immediate.integer);
    }
    return builder;
}
