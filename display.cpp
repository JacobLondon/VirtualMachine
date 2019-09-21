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
    int fcol = 40;
    int instcol = 70;
    int flagcol = 135;
    int spacing = 3;
    std::string buf;

    write_str("Integer Registers", icol, 1);
    for (int i = 0; i < REG_COUNT; i++) {
        buf = to_hex<s64>(mem.iregfile[i]);
        buf += "\t";
        buf += std::to_string(mem.iregfile[i]);
        buf += "\t|";
        write_str(buf, icol, i+spacing);
    }

    write_str("Float Registers", fcol, 1);
    for (int i = 0; i < REG_COUNT; i++) {
        buf = std::to_string(mem.fregfile[i]);
        buf += "\t\t|";
        write_str(buf, fcol, i+spacing);
    }

    write_str("Instructions", instcol, 1);
    int j = 0, i = 0;
    // show instructions around the current pc
    for (i = -REG_COUNT / 2; i < REG_COUNT; i++) {
        if (j >= REG_COUNT)
            break;
        if (mem.pc() + i >= 0 && mem.pc() + i < mem.imem.size()) {
            buf = std::to_string(mem.pc() + i) + " ";
            if (mem.pc() == mem.pc() + i)
                buf += ">>>\t";
            else
                buf += "    \t";
            buf += mem.imem[mem.pc() + i].to_string();
            buf += "\t|";
            write_str(buf, instcol, j+spacing);
            j++;
        }
    }
    // clear the extraneous rows
    for (; j < REG_COUNT; j++) {
        write_str("\t\t\t\t\t\t\t\t", instcol, j+spacing);
    }

    // flags
    write_str("Flags", flagcol, 1);
    write_str("CS  ( Carry )\t" + std::to_string(mem.flags.carry),         flagcol, 0 + spacing);
    write_str("ZS ( $ == 0 )\t" + std::to_string(mem.flags.zero),          flagcol, 2 + spacing);
    write_str("NE  ( $ < 0 )\t" + std::to_string(mem.flags.neg),           flagcol, 4 + spacing);
    write_str("EQ ( $ == $ )\t" + std::to_string(mem.flags.equal),         flagcol, 6 + spacing);
    write_str("LT  ( $ < $ )\t" + std::to_string(mem.flags.less_than),     flagcol, 8 + spacing);
    write_str("LE ( $ <= $ )\t" + std::to_string(!mem.flags.greater_than), flagcol, 9 + spacing);
    write_str("GE ( $ >= $ )\t" + std::to_string(!mem.flags.less_than),    flagcol, 10 + spacing);
    write_str("GT  ( $ > $ )\t" + std::to_string(mem.flags.greater_than),  flagcol, 11 + spacing);
    write_str("AL   ( true )\t" + std::to_string(mem.flags.always),        flagcol, 12 + spacing);

    write_str("Press [Ss] to step\t\tPress [space] to toggle step/run mode\n", 0, 40);

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
