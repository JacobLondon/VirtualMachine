#pragma once
#include "types.hpp"
#include "instruction.hpp"

class memory {
public:
    memory(u64 dmem_size);
    
    u8 flags = 0x00;
    u64 pc = 0;
    const u64 zero = 0;
    std::vector<u64> iregfile;
    std::vector<f64> fregfile;
    std::vector<instruction> imem;
    std::vector<u64> dmem;
    std::stack<u64> stack;
    std::unordered_map<std::string, u64> labels;
};
