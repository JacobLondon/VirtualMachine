#pragma once
#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "types.hpp"
#include "memory.hpp"

class Processor {
public:
    
    Memory mem;
    bool done = false;
    
    Processor(Unsigned data_size);
    void execute();
};

#endif // PROCESSOR_H_