#pragma once
#include "types.hpp"
#include "memory.hpp"

class Processor {
public:
    
    Memory mem;
    bool done = false;
    
    Processor(Unsigned data_size);
    void execute();
};
