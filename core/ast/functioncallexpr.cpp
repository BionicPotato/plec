#include "functioncallexpr.hpp"
#include "../visitors/astvisitor.hpp"

FunctionCallExpr::FunctionCallExpr(Token& token, std::unique_ptr<const Expression> callee)
: Expression(token), callee(std::move(callee)) {}

void FunctionCallExpr::accept(ASTVisitor& visitor) const
{
    visitor.doFunctionCallExpr(*this);
}

