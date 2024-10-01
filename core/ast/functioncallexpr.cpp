#include "functioncallexpr.hpp"
#include "../visitors/astvisitor.hpp"
#include "expression.hpp"
#include "variableexpr.hpp"
#include "../exceptions.hpp"
#include <memory>
#include <vector>

using namespace std;

void FunctionCallExpr::accept(ASTVisitor& visitor)
{
    visitor.doFunctionCallExpr(*this);
}