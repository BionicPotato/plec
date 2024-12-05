#include "arrayexpr.hpp"
#include "../visitors/astvisitor.hpp"

void ArrayExpr::accept(ASTVisitor& visitor) const
{
    visitor.doArrayExpr(*this);
}

