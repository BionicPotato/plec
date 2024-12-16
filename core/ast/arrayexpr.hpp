#pragma once

#include "expression.hpp"
#include <vector>

class Expression;

class ArrayExpr: public Expression
{
    public:
        /*const*/ std::vector<std::unique_ptr<const Expression>> expressions;

        ArrayExpr(Token& token, std::vector<std::unique_ptr<const Expression>>&& expressions);
        virtual void accept(ASTVisitor& visitor) const;
};

