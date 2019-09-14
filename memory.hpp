#pragma once
#include "types.hpp"
#include "instruction.hpp"

const u8 VFLAG = 0x1;
const u8 CFLAG = 0x2;
const u8 ZFLAG = 0x4;
const u8 NFLAG = 0x8;

class memory {
public:
    memory(u64 dmem_size);
    
    u8 flags = 0x00;
    u64 pc = 0;
    const u64 zero = 0;
    std::vector<s64> iregfile;
    std::vector<f64> fregfile;
    std::vector<instruction> imem;
    std::vector<s64> dmem;

    std::stack<s64> data_stack;
    std::stack<u64> call_stack;
    std::unordered_map<std::string, u64> labels;

    // get flags
    inline bool status_v();
    inline bool status_c();
    inline bool status_z();
    inline bool status_n();

    bool suffix(instruction inst);
    void set_flags(s64 result);
};
