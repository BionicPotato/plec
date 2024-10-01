#pragma once

#include "expression.hpp"
#include "operatorexpression.hpp"
#include <memory>

class AddExpr: public OperatorExpression
{
    public:
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;

        using OperatorExpression::OperatorExpression;
        virtual void accept(ASTVisitor& visitor);
        virtual void assignOperands(std::shared_ptr<Expression> a, std::shared_ptr<Expression> b);
};