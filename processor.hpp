#pragma once
#include "types.hpp"
#include "memory.hpp"

class processor {
public:
    processor(u64 data_size);

    void execute(std::vector<instruction> instructions);

    memory mem;
};
