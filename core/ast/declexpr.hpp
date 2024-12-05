#pragma once

#include "binopexpression.hpp"

class DeclExpr: public BinOpExpression
{
    public:
        using BinOpExpression::BinOpExpression;
        virtual void accept(ASTVisitor& visitor) const;
};

