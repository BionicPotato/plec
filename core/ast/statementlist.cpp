#include "../visitors/astvisitor.hpp"
#include "statementlist.hpp"

void StatementList::accept(ASTVisitor& visitor)
{
    visitor.doStatementList(*this);
}

