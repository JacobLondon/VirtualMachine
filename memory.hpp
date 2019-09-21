#pragma once
#include "types.hpp"

class Memory {
public:
    Memory(u64 dmem_size);
    std::string dump();
    s64 zero();
    s64 pc();
    void pc_rst();
    void pc_inc();
    void pc_jmp(s64 address);
    void clear_flags();
    void set_flags(f64 result);

    struct flags {
        bool carry        = false;
        bool zero         = false;
        bool neg          = false;
        bool equal        = false;
        bool less_than    = false;
        bool greater_than = false;
        bool always       = true;
    } flags;
    
    std::vector<s64> iregfile;
    std::vector<f64> fregfile;
    std::vector<Instruction> imem;
    std::vector<s64> dmem;

    std::stack<s64> data_stack;
    std::stack<u64> call_stack;
    std::unordered_map<std::string, u64> labels;

};

#include "instruction.hpp"
