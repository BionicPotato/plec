#include "../visitors/astvisitor.hpp"
#include "../runner.hpp"
#include "statement.hpp"

Statement::Statement(Token& token): token(token) {}

void Statement::accept(ASTVisitor& visitor) const
{
    visitor.doStatement(*this);
}

void Statement::run(Runner& r) const {}

