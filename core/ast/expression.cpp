#include "expression.hpp"
#include "../visitors/astvisitor.hpp"

void Expression::accept(ASTVisitor& visitor) const
{
    visitor.doExpression(*this);
}

