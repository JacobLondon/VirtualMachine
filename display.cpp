#include <string>
#include <chrono> // sleep
#include <thread> // sleep
#include <iomanip> // hex
#include <sstream> // hex
#include "display.hpp"

Display::Display()
{
    
}

Display::~Display()
{
    clear();
    endwin();
}

void Display::startup()
{
    initscr();
    clear();
    cbreak();
    noecho();
    nodelay(stdscr, true);
}

template<typename T>
static std::string to_hex(T i)
{
    std::stringstream stream;
    stream << "0x"
           << std::setfill('0') << std::setw(sizeof(T) * 2)
           << std::hex << i;
    return stream.str();
}

static void write_str(std::string s, int x, int y)
{
    move(y, x);
    addstr(s.c_str());
    refresh();
}

void Display::update(Memory& mem)
{
    int icol = 5;
    int fcol = 30;
    std::string buf;

    write_str("Integer Registers", icol, 1);
    for (int i = 0; i < REG_COUNT; i++) {
        buf = to_hex<s64>(mem.iregfile[i]);
        buf += "\t";
        buf += std::to_string(mem.iregfile[i]);
        write_str(buf, icol, i+3);
    }

    write_str("Float Registers", fcol, 1);
    for (int i = 0; i < REG_COUNT; i++) {
        buf = std::to_string(mem.fregfile[i]);
        write_str(buf, fcol, i+3);
    }

    handle_keys();
}

void Display::handle_keys()
{
    int ch = 0;
    while (step) {
        if ((ch = getch()) == ERR)
            ;
        else {
            switch (ch) {
            case 'S': // step
            case 's':
                return;
            case 32: // space
                step = !step;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                return;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
