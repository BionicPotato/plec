#pragma once

#include "expression.hpp"
#include <vector>

class Expression;

class FunctionCallExpr: public Expression
{
    public:
        const std::unique_ptr<const Expression> callee;
        const std::vector<std::unique_ptr<const Expression>> args;

        FunctionCallExpr(Token& token, std::unique_ptr<const Expression> callee, std::vector<std::unique_ptr<const Expression>>&& args);
        virtual void accept(ASTVisitor& visitor) const;
};

