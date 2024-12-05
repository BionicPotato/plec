#include "../visitors/astvisitor.hpp"
#include "statementlist.hpp"

void StatementList::accept(ASTVisitor& visitor) const
{
    visitor.doStatementList(*this);
}

