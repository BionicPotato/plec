#include "../visitors/astvisitor.hpp"
#include "statementlist.hpp"

StatementList::StatementList(std::vector<std::unique_ptr<const Statement>>&& statements)
: statements(std::move(statements)) {}

void StatementList::accept(ASTVisitor& visitor) const
{
    visitor.doStatementList(*this);
}

