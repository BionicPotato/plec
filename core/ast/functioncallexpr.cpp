#include "functioncallexpr.hpp"
#include "../visitors/astvisitor.hpp"

void FunctionCallExpr::accept(ASTVisitor& visitor)
{
    visitor.doFunctionCallExpr(*this);
}

