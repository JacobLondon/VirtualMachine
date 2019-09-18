#pragma once
#include "types.hpp"

enum MemoryFlags {
    V_FLAG = 0x1,
    C_FLAG = 0x2,
    Z_FLAG = 0x4,
    N_FLAG = 0x8,
};

class Memory {
public:
    Memory(u64 dmem_size);
    std::string dump();
    s64 zero();
    s64 pc();
    void pc_rst();
    void pc_inc();
    void pc_jmp(s64 address);

    u8 flags = 0;
    std::vector<s64> iregfile;
    std::vector<f64> fregfile;
    std::vector<Instruction> imem;
    std::vector<s64> dmem;

    std::stack<s64> data_stack;
    std::stack<u64> call_stack;
    std::unordered_map<std::string, u64> labels;

    // get flags
    bool status_v();
    bool status_c();
    bool status_z();
    bool status_n();

};

#define MEM_SET_FLAGS(mem, target, check1, check2) do { \
    mem.flags = 0; \
    /* overflow */ \
    if ((check1 > 0) && (check1 > REG_MAX(target) - check2)) \
        mem.flags |= V_FLAG; \
    /* underflow */ \
    if ((check1 < 0) && (check1 < REG_MIN(target) - check2)) \
        mem.flags |= V_FLAG; \
    /* carry */ \
    if ((check1 - check2) < 0) \
        mem.flags |= C_FLAG; \
    /* zero */ \
    if (check1 - check2 == 0) \
        mem.flags |= Z_FLAG; \
    /* negative */ \
    if (check1 - check2 < 0) \
        mem.flags |= N_FLAG; \
} while (0)

#include "instruction.hpp"
