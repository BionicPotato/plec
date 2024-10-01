#pragma once

#include "astvisitable.hpp"
#include <memory>

class Runner;

class Statement: public ASTVisitable, public std::enable_shared_from_this<Statement>
{
    public:
        virtual void accept(ASTVisitor& visitor);
        virtual void run(Runner& r) {}
};