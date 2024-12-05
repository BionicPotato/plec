#pragma once

#include "expression.hpp"
#include <vector>

class Expression;

class ArrayExpr: public Expression
{
    public:
        std::vector<std::unique_ptr<const Expression>> expressions;

        using Expression::Expression;
        virtual void accept(ASTVisitor& visitor) const;
};

