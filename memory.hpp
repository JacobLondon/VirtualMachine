#pragma once
#include <stack>
#include <unordered_map>
#include "types.hpp"

class Memory {
public:
    
    std::vector<Signed> iregfile;
    std::vector<Float> fregfile;
    std::vector<Instruction> imem;
    std::vector<Signed> dmem;
    std::stack<Signed> data_stack;
    std::stack<Unsigned> call_stack;
    std::unordered_map<std::string, Unsigned> labels;

    Memory(size_t dmem_size);
    void insert(Instruction inst);

    Signed zero();
    Signed pc();
    void pc_rst();
    void pc_inc();
    void pc_jmp(Signed address);

    void clear_flags();
    void set_flags(Float result);
    struct flags {
        bool carry        = false;
        bool zero         = false;
        bool neg          = false;
        bool equal        = false;
        bool less_than    = false;
        bool greater_than = false;
        bool always       = true;
    } flags;
};

#include "instruction.hpp"
