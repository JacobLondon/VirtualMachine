#pragma once
#include "types.hpp"
#include "memory.hpp"

class Processor {
public:
    Processor(Unsigned data_size);

    void execute();
    Memory mem;
    bool done = false;

};
