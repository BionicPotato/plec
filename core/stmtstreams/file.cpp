#include "file.hpp"
#include "../ast/programstmt.hpp"
#include "../ast/statement.hpp"
#include "../exceptions.hpp"

using namespace std;

bool FileStmtStream::getNextToken(Token& tok)
{
    return lexp->getNextToken(tok);
}

bool FileStmtStream::checkCurlyBr(const Token& tok)
{
    if (tok.id == TOK_CLOSECURLYBR) throw UnexpectedTokenException(tok);
    return false;
}

bool FileStmtStream::checkProgramStmt(Token& tok, unique_ptr<const Statement>& stp)
{
    if (tok.id == TOK_PROGRAM) {
        Token progtok = tok;
        getNextToken(tok);
        if (tok.id != TOK_IDENTIFIER)
            throw UnexpectedTokenException(tok);
        Token t2;
        getNextToken(t2);
        if (t2.id != TOK_SEMICOLON)
            throw UnexpectedTokenException(t2);
        stp = make_unique<ProgramStmt>(progtok, tok.content);
        return true;
    }
    return false;
}

