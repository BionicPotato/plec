#pragma once

#include "expression.hpp"
#include <vector>

class BlockExpr: public Expression
{
    public:
        std::vector<std::shared_ptr<Statement>> statements;

        using Expression::Expression;
        virtual void accept(ASTVisitor& visitor);
};