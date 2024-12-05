#include "block.hpp"
#include "../exceptions.hpp"
#include "../ast/expression.hpp"

bool BlockStmtStream::getNextToken(Token& tok)
{
    return lexp->getNextToken(tok);
}

bool BlockStmtStream::checkCurlyBr(const Token& tok)
{
    return tok.id == TOK_CLOSECURLYBR;
}

bool BlockStmtStream::checkProgramStmt(Token& tok, std::unique_ptr<const Statement>& stp)
{
    if (tok.id == TOK_PROGRAM) throw UnexpectedTokenException(tok);
    return false;
}

