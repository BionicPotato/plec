#include "arrayexpr.hpp"
#include "../visitors/astvisitor.hpp"

void ArrayExpr::accept(ASTVisitor& visitor)
{
    visitor.doArrayExpr(*this);
}

