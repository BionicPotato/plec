#include "blockexpr.hpp"
#include "../visitors/astvisitor.hpp"

BlockExpr::BlockExpr(Token& token, std::unique_ptr<const ArrayExpr> dataBlock, std::unique_ptr<const CurlyBrExpr> statementBlock)
: Expression(token), dataBlock(std::move(dataBlock)), statementBlock(std::move(statementBlock)) {}

void BlockExpr::accept(ASTVisitor& visitor) const
{
    visitor.doBlockExpr(*this);
}

