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

void VariableAssignExpr::assignOperands(shared_ptr<Expression> a, shared_ptr<Expression> b)
{
    const Expression* _a = a.get();
    const type_info& t_a = typeid(*_a);
    const type_info& t_ve = typeid(VariableExpr);
    if (t_a != t_ve)
        throw BadAssignException(t_a.name(), a, t_ve.name());
    
    variable = static_pointer_cast<VariableExpr>(a);
    value = b;
}

