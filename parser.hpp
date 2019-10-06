#pragma once
#ifndef PARSER_H_
#define PARSER_H_

#include "types.hpp"

class Parser {
    const std::string& filename;
public:
    Parser(const std::string& filename);
    std::vector<Instruction> parse();
};

using line_t = unsigned long long;
struct DebugInfo {
    DebugInfo(const line_t& lineNum,
            const std::string& lineValue);
    void print() const;
    line_t lineNum;
    std::string originalLineValue;
};

#endif // PARSER_H_
