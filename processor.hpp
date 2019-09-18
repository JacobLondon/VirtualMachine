#pragma once
#include "types.hpp"
#include "memory.hpp"

class Processor {
public:
    Processor(u64 data_size);

    void execute();
    Memory mem;
    bool done = false;

};
