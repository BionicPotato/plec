#pragma once

#include "expressions.hpp"
#include <vector>

class Expression;

class FunctionCallExpr: public Expression
{
    public:
        std::shared_ptr<Expression> callee;
        std::shared_ptr<ArrayExpr> args;

        using Expression::Expression;
        virtual void accept(ASTVisitor& visitor);
};
