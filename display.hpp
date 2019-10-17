#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

extern "C" {
#include <ncurses.h>
}

#include "memory.hpp"

class Display {
public:

    Memory *mem;
    bool step = true;

    Display(Memory *mem);
    ~Display();
    void startup();
    void update();
    void handle_keys();
};

#endif // DISPLAY_H_