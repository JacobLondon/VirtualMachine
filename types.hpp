#pragma once
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#define WIDTH_64

#ifdef WIDTH_64
using Float    = double;
using Signed   = int64_t;
using Unsigned = uint64_t;
#else
using Float    = float;
using Signed   = int32_t;
using Unsigned = uint32_t;
#endif

class Instruction;
//class Memory;
//class Processor;

const uint8_t REG_COUNT = 32;
const uint8_t ZERO = 0;
const uint8_t PC = 31;

enum Registers {
    // integer registers
    R0, R1, R2, R3, R4, R5, R6, R7, R8, R9,
    R10, R11, R12, R13, R14, R15, R16, R17, R18, R19,
    R20, R21, R22, R23, R24, R25, R26, R27, R28, R29,
    R30, R31,
    // floating point registers
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9,
    F10, F11, F12, F13, F14, F15, F16, F17, F18, F19,
    F20, F21, F22, F23, F24, F25, F26, F27, F28, F29,
    F30, F31,
};

enum Suffixes {
    CS, CC,     // carry s/c
    ZS, ZC,     // zero s/c
    NS, NC,     // negative s/c
    EQ,         // equal
    NE,         // not equal
    LT, GE,     // less than, greater than or equal to
    GT, LE,     // greater than, less than or equal to
    AL,         // always
};

const std::vector<std::string> SUFFIX_LOOKUP {
    "CS", "CC",
    "ZS", "ZC",
    "NS", "NC",
    "EQ",
    "NE",
    "LT", "GE",
    "GT", "LE",
    "", // AL blank
};

enum Opcodes {
    NOP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    AND,
    XOR,
    OR,
    NOT,
    COMP,
    SHR,
    SHL,
    CMP,
    SWP,
    MOV,
    SET,
    CLR,
    SW,
    LW,
    INC,
    DEC,
    PUSH,
    POP,
    JMP,
    CALL,
    RET,
};

const std::vector<std::string> OPCODE_LOOKUP {
    "NOP",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "AND",
    "XOR",
    "OR",
    "NOT",
    "COMP",
    "SHR",
    "SHL",
    "CMP",
    "SWP",
    "MOV",
    "SET",
    "CLR",
    "SW",
    "LW",
    "INC",
    "DEC",
    "PUSH",
    "POP",
    "JMP",
    "CALL",
    "RET",
};
