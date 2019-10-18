#include "parser.hpp"

#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <cstdlib>

#include "instruction.hpp"

Parser::Parser(const std::string& filename)
    : filename(filename)
{}

void trim(std::string& line) {
    // Trim comments
    auto commentChar = [] (char c) {
        return c == '#';
    };
    auto startOfComment = std::find_if(line.begin(), line.end(), commentChar);
    line.erase(startOfComment, line.end());

    // Trim the string
    auto isntSpace = [] (char c) {
        return !std::isspace(c);
    };
    auto firstNonSpace = std::find_if(line.begin(), line.end(), isntSpace);
    line.erase(line.begin(), firstNonSpace);
    auto lastSpace = std::find_if(line.rbegin(), line.rend(), isntSpace);
    line.erase(lastSpace.base(), line.end());
}

Parser::InstLabelPair Parser::parse()
{
    InstList instructions;
    LabelMap labels;

    // Open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File \"" << filename << "\" not found." << std::endl;
        std::abort();
    }

    // Loop through the file
    line_t lineNum = 0;
    std::string line;
    while (!file.eof()) {
        // Get line
        lineNum++;
        std::getline(file, line);
        DebugInfo info(lineNum, line);

        // Skip if empty or comment
        trim(line);
        if (line.empty()) {
            continue;
        }

        // Check this line is a label
        if (line.back() == ':') {
            line.pop_back();
            labels[line] = instructions.size();
            info.print();
            std::cout << line << ": Label \"" << line << "\"" << std::endl;
            continue;
        }

        // Decode
        


        info.print();
        std::cout << line << ", " << line.size() << std::endl;
    }

    // Return
    return std::make_pair(instructions, labels);
}

DebugInfo::DebugInfo(const line_t& lineNum,
                     const std::string& lineValue)
    : lineNum(lineNum), originalLineValue(lineValue)
{}

void DebugInfo::print() const {
#ifdef DEBUG
    std::cout << lineNum << ": " << originalLineValue << std::endl;
#endif
}
