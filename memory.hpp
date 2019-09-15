#pragma once
#include "types.hpp"
#include "instruction.hpp"

enum MemoryFlags {
    VFLAG = 0x1,
    CFLAG = 0x2,
    ZFLAG = 0x4,
    NFLAG = 0x8,
};

class Memory {
public:
    Memory(u64 dmem_size);
    
    u8 flags = 0;
    u64 pc = 0;
    const u64 zero = 0;
    std::vector<s64> iregfile;
    std::vector<f64> fregfile;
    std::vector<Instruction> imem;
    std::vector<s64> dmem;

    std::stack<s64> data_stack;
    std::stack<u64> call_stack;
    std::unordered_map<std::string, u64> labels;

    // get flags
    inline bool status_v();
    inline bool status_c();
    inline bool status_z();
    inline bool status_n();

    void set_flags(f64 result);
    void set_flags(s64 result);
};
