#pragma once
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using f64 = double;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s64 = int64_t;

class Instruction;
class Memory;
class Processor;

const u32 FREG_START = 32;
const u32 REG_LENGTH = 32;

enum IRegisters {
    // integer registers
    R0, R1, R2, R3, R4, R5, R6, R7, R8, R9,
    R10, R11, R12, R13, R14, R15, R16, R17, R18, R19,
    R20, R21, R22, R23, R24, R25, R26, R27, R28, R29,
    R30, R31,
};
enum FRegisters {
    // floating point registers
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9,
    F10, F11, F12, F13, F14, F15, F16, F17, F18, F19,
    F20, F21, F22, F23, F24, F25, F26, F27, F28, F29,
    F30, F31,
};

enum Suffixes {
    EQ,
    NE,
    CS, HS,
    CC, LO,
    MI,
    PL,
    VS,
    VC,
    HI,
    LS,
    GE,
    LT,
    GT,
    LE,
    AL,
};

enum Opcodes {
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
    B,
    CALL,
    RET,
};
