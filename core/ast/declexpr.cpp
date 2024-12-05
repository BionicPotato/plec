#include "../visitors/astvisitor.hpp"
#include "declexpr.hpp"

using namespace std;

void DeclExpr::accept(ASTVisitor& visitor) const
{
    visitor.doDeclExpr(*this);
}

