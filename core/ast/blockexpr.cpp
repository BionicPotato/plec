#include "blockexpr.hpp"
#include "../visitors/astvisitor.hpp"

void BlockExpr::accept(ASTVisitor& visitor)
{
    visitor.doBlockExpr(*this);
}

