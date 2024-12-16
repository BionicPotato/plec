#include "arrayexpr.hpp"
#include "../visitors/astvisitor.hpp"

ArrayExpr::ArrayExpr(Token& token, std::vector<std::unique_ptr<const Expression>>&& expressions)
: Expression(token), expressions(std::move(expressions)) {}

void ArrayExpr::accept(ASTVisitor& visitor) const
{
    visitor.doArrayExpr(*this);
}

