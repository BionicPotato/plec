#include "../exceptions.hpp"
#include "../visitors/astvisitor.hpp"
#include "variableassignexpr.hpp"
#include "variableexpr.hpp"
#include <memory>
#include <typeinfo>

#include <iostream>

using namespace std;

void VariableAssignExpr::accept(ASTVisitor& visitor)
{
    visitor.doVariableAssignExpr(*this);
}

