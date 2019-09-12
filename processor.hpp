#pragma once
#include "types.hpp"
#include "memory.hpp"

class processor {
public:
    processor(u64 data_size);

    std::vector<std::string> tokenize(std::string assembly);
    std::vector<instruction> assemble(std::vector<std::string> tokens);
    void execute(std::vector<instruction> instructions);
    void format(std::string opcode, std::string suffix, std::string register);

    std::unordered_map<std::string, u8> opcodes;
    std::unordered_map<std::string, u8> suffices;
    std::unordered_map<std::string, u8> registers;

    u64 data_size = 0; // * 64
    memory mem;
};
