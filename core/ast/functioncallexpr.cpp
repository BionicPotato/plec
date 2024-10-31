#include "functioncallexpr.hpp"
#include "../visitors/astvisitor.hpp"

FunctionCallExpr::FunctionCallExpr(Token& token, std::shared_ptr<Expression> callee)
: Expression(token), callee(callee) {}

void FunctionCallExpr::accept(ASTVisitor& visitor)
{
    visitor.doFunctionCallExpr(*this);
}

