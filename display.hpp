#pragma once
extern "C" {
#include <ncurses.h>
}
#include "memory.hpp"

class Display {
public:
    Display();
    ~Display();
    void startup();
    void update(Memory& mem);
    void handle_keys();

    bool step = true;
};
