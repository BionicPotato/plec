#include "blockexpr.hpp"
#include "../visitors/astvisitor.hpp"

void BlockExpr::accept(ASTVisitor& visitor) const
{
    visitor.doBlockExpr(*this);
}

