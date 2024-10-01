#pragma once

#include "operatorexpression.hpp"
#include <vector>

class Expression;

class FunctionCallExpr: public Expression
{
    public:
        std::shared_ptr<Expression> callee;
        std::vector<std::shared_ptr<Expression>> args;

        using Expression::Expression;
        virtual void accept(ASTVisitor& visitor);
};
