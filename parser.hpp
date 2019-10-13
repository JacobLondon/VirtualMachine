#pragma once
#ifndef PARSER_H_
#define PARSER_H_

#include <unordered_map>

#include "types.hpp"

class Parser {
    const std::string& filename;
public:
    using InstList = std::vector<Instruction>;
    using InstIndex = size_t;
    using LabelMap = std::unordered_map<std::string, InstIndex>;
    using InstLabelPair = std::pair<InstList, LabelMap>;
    Parser(const std::string& filename);
    InstLabelPair parse();
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
