#pragma once

#include "expression.hpp"
#include "arrayexpr.hpp"
#include "curlybrexpr.hpp"

class BlockExpr: public Expression
{
    public:
        const std::unique_ptr<const ArrayExpr> dataBlock;
        const std::unique_ptr<const CurlyBrExpr> statementBlock;

        BlockExpr(Token& token, std::unique_ptr<const ArrayExpr> dataBlock, std::unique_ptr<const CurlyBrExpr> statementBlock);
        virtual void accept(ASTVisitor& visitor) const;
};

