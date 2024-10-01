#include "../visitors/astvisitor.hpp"
#include "addexpr.hpp"

using namespace std;

void AddExpr::accept(ASTVisitor& visitor)
{
    visitor.doAddExpr(*this);
}

void AddExpr::assignOperands(shared_ptr<Expression> a, shared_ptr<Expression> b)
{
    lhs = a;
    rhs = b;
}