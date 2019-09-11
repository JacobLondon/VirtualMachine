#pragma once
#include "types.h"
#include "instruction.h"

class memory {
public:
    memory();
    memory(u64 inst_size, u64 data_size, u64 reg_file_size);

    std::vector<u64> register_file;
    u8 flags = 0x00;
    std::vector<instruction> instruction_memory;
    std::vector<u64> data_memory;
    std::stack<u64> stack;
    std::unordered_map<std::string, u64> labels;
};
