#include "blockexpr.hpp"
#include "../visitors/astvisitor.hpp"

BlockExpr::BlockExpr(Token& token, std::vector<std::unique_ptr<const Statement>>&& statements)
: Expression(token), statements(std::move(statements)) {}

void BlockExpr::accept(ASTVisitor& visitor) const
{
    visitor.doBlockExpr(*this);
}

