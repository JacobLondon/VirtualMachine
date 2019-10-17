#pragma once
extern "C" {
#include <ncurses.h>
}
#include "memory.hpp"

class Display {
public:
    Display(Memory *mem);
    ~Display();
    void startup();
    void update();
    void handle_keys();

    Memory *mem;
    bool step = true;
};
