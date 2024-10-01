#pragma once

#include "target.hpp"

class Program: public Target
{
    public:
        Program(const std::string& name);
};