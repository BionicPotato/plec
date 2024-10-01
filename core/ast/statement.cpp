#include "../visitors/astvisitor.hpp"
#include "statement.hpp"

void Statement::accept(ASTVisitor& visitor)
{
    visitor.doStatement(*this);
}