#pragma once

#include "expression.hpp"
#include <vector>

class CurlyBrExpr: public Expression
{
    public:
        const std::vector<std::unique_ptr<const Statement>> statements;

        CurlyBrExpr(Token& token, std::vector<std::unique_ptr<const Statement>>&& statements);
        virtual void accept(ASTVisitor& visitor) const;
};

