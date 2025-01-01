#include "curlybrexpr.hpp"
#include "../visitors/astvisitor.hpp"

CurlyBrExpr::CurlyBrExpr(Token& token, std::vector<std::unique_ptr<const Statement>>&& statements)
: Expression(token), statements(std::move(statements)) {}

void CurlyBrExpr::accept(ASTVisitor& visitor) const
{
    visitor.doCurlyBrExpr(*this);
}

