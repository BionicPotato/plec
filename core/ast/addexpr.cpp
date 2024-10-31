#include "../visitors/astvisitor.hpp"
#include "addexpr.hpp"

using namespace std;

void AddExpr::accept(ASTVisitor& visitor)
{
    visitor.doAddExpr(*this);
}

