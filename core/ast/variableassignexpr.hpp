#pragma once

#include "expression.hpp"
#include "binopexpression.hpp"
#include "variableexpr.hpp"

class VariableAssignExpr: public BinOpExpression
{
    public:
        using BinOpExpression::BinOpExpression;
        virtual void accept(ASTVisitor& visitor) const;
};

