#pragma once

#include <cstdint>
#include <list>
#include "token.hpp"

struct CSTNode
{
    std::list<CSTNode*> LHSChildren;
    std::list<CSTNode*> RHSChildren;
    Token token;
    int8_t enclosing;
    uint8_t lhs;
    uint8_t rhs;
    uint8_t precedence;
};