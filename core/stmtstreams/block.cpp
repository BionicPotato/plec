#include "block.hpp"
#include "../exceptions.hpp"
#include "../ast/expression.hpp"

bool BlockStmtStream::getNextToken(Token& tok)
{
    return lexp->getNextToken(tok);
}

bool BlockStmtStream::checkProgramStmt(Token& tok, std::shared_ptr<Statement>& stp)
{
    if (tok.id == TOK_PROGRAM) throw UnexpectedTokenException(tok);
    return false;
}

bool BlockStmtStream::getNextStatement(std::shared_ptr<Statement>& stp)
{
    Token tok;
    if (!getNextToken(tok)) return false;
    if (tok.id == TOK_CLOSECURLYBR) return false;
    if (tok.id == TOK_PROGRAM) throw UnexpectedTokenException(tok);
    else stp = getExpression(tok, TOK_SEMICOLON);
    return true;
}

