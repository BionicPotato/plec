#include "expression.hpp"
#include "../visitors/astvisitor.hpp"

Expression::Expression(Token& token): token(token) {}

void Expression::accept(ASTVisitor& visitor)
{
    visitor.doExpression(*this);
}
