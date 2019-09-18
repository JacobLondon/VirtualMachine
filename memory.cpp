#include <limits>
#include <iomanip>
#include <sstream>
#include "memory.hpp"

/**
 * util
 */

template<typename T>
static std::string to_hex(T i)
{
    std::stringstream stream;
    stream << "0x" 
           << std::setfill ('0') << std::setw(sizeof(T) * 2) 
           << std::hex << i;
    return stream.str();
}

static std::vector<char> to_bytes(const std::string& hex)
{
    std::vector<char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = (char)strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

/**
 * Memory
 */

Memory::Memory(u64 dmem_size)
    : iregfile(REG_COUNT, 0), fregfile(REG_COUNT, 0.0)
{
    dmem.reserve(dmem_size);
}

std::string Memory::dump()
{
    u32 len = 80;
    std::string builder = "";

    for (u64 i = 0; i < len; i++)
        builder += "_";
    builder += "\n\n";

    builder += "\t\tInteger Registers\t\t\tFloat Registers\n";

    for (u64 i = 0; i < len; i++)
        builder += "_";
    builder += "\n";

    for (u64 i = 0; i < iregfile.size(); i++) {

        std::string reg_hex = to_hex<s64>(iregfile[i]);
        std::vector<char> reg_bytes = to_bytes(reg_hex);

        builder += std::to_string(i) + ((i == 0) ? " Zero\t" : (i == 31) ? " PC\t" : "\t");
        builder += reg_hex + "\t";

        // ascii
        for (char c : reg_bytes) {
            if (c == 0)
                builder += ". ";
            else
                builder += c + " ";
        }

        builder += "\t|\t" + std::to_string(fregfile[i]) + "\n";
    }

    builder += "\nFlags: " + to_hex<u8>(flags) + "\n";

    return builder;
}

s64 Memory::zero()
{
    return iregfile[0];
}

s64 Memory::pc()
{
    return iregfile[iregfile.size() - 1];
}

void Memory::pc_rst()
{
    iregfile[iregfile.size() - 1] = 0;
}

void Memory::pc_jmp(s64 address)
{
    iregfile[iregfile.size() - 1] = address;
}

void Memory::pc_inc()
{
    iregfile[iregfile.size() - 1]++;
}

/**
 * statuses
 */

bool Memory::status_v()
{
    return flags & V_FLAG;
}

bool Memory::status_c()
{
    return flags & C_FLAG;
}

bool Memory::status_z()
{
    return flags & Z_FLAG;
}

bool Memory::status_n()
{
    return flags & N_FLAG;
}
