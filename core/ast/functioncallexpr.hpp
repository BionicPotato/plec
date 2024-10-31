#pragma once

#include "expression.hpp"
#include <vector>

class Expression;

class FunctionCallExpr: public Expression
{
    public:
        std::shared_ptr<Expression> callee;
        std::vector<std::shared_ptr<Expression>> args;

        FunctionCallExpr(Token& token, std::shared_ptr<Expression> callee);
        virtual void accept(ASTVisitor& visitor);
};
