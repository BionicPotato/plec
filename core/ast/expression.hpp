#pragma once

#include "statement.hpp"
#include "../token.hpp"

class Expression: public Statement
{
    public:
        using Statement::Statement;
        virtual void accept(ASTVisitor& visitor) const;
};
