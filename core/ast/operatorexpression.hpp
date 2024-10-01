#pragma once

#include "expression.hpp"
#include <memory>

class OperatorExpression: public Expression
{
    public:
        using Expression::Expression;

        virtual void assignOperands(std::shared_ptr<Expression> a, std::shared_ptr<Expression> b) = 0;
};