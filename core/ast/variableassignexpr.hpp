#pragma once

#include "expression.hpp"
#include "operatorexpression.hpp"
#include "variableexpr.hpp"

class VariableAssignExpr: public OperatorExpression
{
    public:
        std::shared_ptr<VariableExpr> variable;
        std::shared_ptr<Expression> value;

        using OperatorExpression::OperatorExpression;
        virtual void accept(ASTVisitor& visitor);
        virtual void assignOperands(std::shared_ptr<Expression> a, std::shared_ptr<Expression> b);
};

