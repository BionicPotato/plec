#pragma once

#include "expression.hpp"
#include <vector>

class BlockExpr: public Expression
{
    public:
        std::vector<std::unique_ptr<const Statement>> statements;

        using Expression::Expression;
        virtual void accept(ASTVisitor& visitor) const;
};
