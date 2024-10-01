#include "block.hpp"
#include "../exceptions.hpp"

bool BlockStmtStream::getNextToken(Token& tok)
{
    return lexp->getNextToken(tok);
}

bool BlockStmtStream::checkProgramStmt(Token& tok, std::shared_ptr<Statement>& stp)
{
    if (tok.id == TOK_PROGRAM) throw UnexpectedTokenException(tok);
    return false;
}