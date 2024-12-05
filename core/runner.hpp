#pragma once

#include "ast/targettype.hpp"
#include "ast/file.hpp"
#include <memory>
#include <string>

class Statement;

class Runner
{
    public:
        virtual void setTarget(std::string filename, TargetType targetType, std::string targetName) = 0;
};
