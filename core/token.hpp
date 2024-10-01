#pragma once

#include <cstdint>
#include <string>
#include "tokenid.hpp"

struct Token
{
    TokenID id;
    std::string content;
    const char* filename;
    unsigned lineNo;
    unsigned colNo;
};
