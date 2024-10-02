#include "../visitors/astvisitor.hpp"
#include "../runner.hpp"
#include "statement.hpp"

void Statement::accept(ASTVisitor& visitor)
{
    visitor.doStatement(*this);
}

void Statement::run(Runner& r)
{
    r.addToTarget(shared_from_this());
}
