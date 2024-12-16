#pragma once

#include "expression.hpp"
#include <vector>

class BlockExpr: public Expression
{
    public:
        const std::vector<std::unique_ptr<const Statement>> statements;

        BlockExpr(Token& token, std::vector<std::unique_ptr<const Statement>>&& statements);
        virtual void accept(ASTVisitor& visitor) const;
};

