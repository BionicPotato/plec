#pragma once

#include "astvisitable.hpp"
#include "../token.hpp"
#include <memory>

class Runner;

class Statement: public ASTVisitable, public std::enable_shared_from_this<Statement>
{
    public:
        Token token;

        Statement(Token& token);
        virtual void accept(ASTVisitor& visitor) const;
        virtual void run(Runner& r) const;
};

