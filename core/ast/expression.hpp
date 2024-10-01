#pragma once

#include "statement.hpp"
#include "../token.hpp"

class Expression: public Statement
{
    public:
        Token token;

        Expression(Token& token);
        virtual void accept(ASTVisitor& visitor);
};