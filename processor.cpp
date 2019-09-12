#include "processor.hpp"

processor::processor(u64 data_size)
    : data_size(data_size)
{
    format(
        "add sub mul div mod nand and xnor xor nor or shr sra shl ror rol cmp swp mov set clr ww rw b call ret",
        "eq ne cs hs cc lo mi pl vs vc hi ls ge lt gt le al",
        "zero pc r30"
    );
}

std::vector<std::string> processor::tokenize(std::string assembly)
{
    std::vector<std::string> tokens;

    for (u64 i = 0; i < assembly.size(); i++) {
        for (auto &op : opcodes) {
            if (op.first.size() + i > assembly.size())
                continue;
            
            // match
            u8 opcode;
            u8 suffix;

            if (op.first == assembly.substr(i, op.first.size())) {
                
            }
        }
    }
}

std::vector<instruction> processor::assemble(std::vector<std::string> tokens)
{
    std::vector<instruction> instructions;

}

void processor::execute(std::vector<instruction> instructions)
{
    mem = memory{instructions.size(), data_size, 32};
}


static void split(const std::string& string_in, char delim, std::vector<std::string>& tokens_out)
{
    std::istringstream iss(string_in);
    std::string token;
 
    while (std::getline(iss, token, delim)) {
        tokens_out.push_back(token);
    }
}

void processor::format(std::string opcode, std::string suffix, std::string reg)
{
    opcodes.clear();
    suffices.clear();
    registers.clear();

    std::vector<std::string> temp;

    split(opcode, ' ', temp);
    for (int i = 0; i < temp.size(); i++)
        opcodes[temp[i]] = i;

    temp.clear();
    split(suffix, ' ', temp);
    for (int i = 0; i < temp.size(); i++)
        suffices[temp[i]] = i;

    temp.clear();
    split(reg, ' ', temp);
    for (int i = 0; i < temp.size(); i++) {
        // found a number
        std::string builder = "0";
        int found = 0;
        for (int j = 0; j < temp[i].size(); j++) {
            if (temp[i][j] >= '0' && temp[i][j] <= '9') {
                if (!found)
                    found = j;
                builder += temp[i][j];
            }
        }

        int number = stoi(builder);
        if (found) {
            for (int j = 0; j < number; j++)
                registers[temp[i].substr(0, found) + std::to_string(j)] = i + j;
        }
        else {
            registers[temp[i]] = i;
        }
    }
}
