#pragma once

#include "ast/targettype.hpp"
#include <memory>
#include <string>

class Statement;

class Runner
{
    public:
        virtual void addToTarget(std::shared_ptr<Statement> stp) = 0;
        virtual void setTarget(TargetType targetType, std::string targetName) = 0;
};