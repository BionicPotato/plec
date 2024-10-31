#pragma once

#include "expression.hpp"
#include "binopexpression.hpp"
#include <memory>

class AddExpr: public BinOpExpression
{
    public:
        using BinOpExpression::BinOpExpression;
        virtual void accept(ASTVisitor& visitor);
};
