#include "functioncallexpr.hpp"
#include "../visitors/astvisitor.hpp"

FunctionCallExpr::FunctionCallExpr(Token& token, std::unique_ptr<const Expression> callee, std::vector<std::unique_ptr<const Expression>>&& args)
: Expression(token), callee(std::move(callee)), args(std::move(args)) {}

void FunctionCallExpr::accept(ASTVisitor& visitor) const
{
    visitor.doFunctionCallExpr(*this);
}

