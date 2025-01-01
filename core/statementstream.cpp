#include "asttype.hpp"
#include "statementstream.hpp"
#include "ast/expressions.hpp"
#include "ast/statement.hpp"
#include "stmtstreams/block.hpp"
#include "expressionparsing.hpp"
#include "token.hpp"
#include "ast/programstmt.hpp"
#include "exceptions.hpp"
#include "tokenid.hpp"
#include <list>
#include <stack>
#include <memory>
#include <typeinfo>

using namespace std;

StatementStream::StatementStream(shared_ptr<Lexer> lexp): filename(lexp->filename), lexp(lexp) {}

bool StatementStream::getNextStatement(unique_ptr<const Statement>& stp)
{
    Token tok;
    if (!getNextToken(tok)) return false;
    if (checkCurlyBr(tok)) return false;
    if (checkProgramStmt(tok, stp)) return true;
    else stp = getExpression(tok, TOK_SEMICOLON);
    return true;
}

unique_ptr<Expression> StatementStream::getExpression(const Token& start, TokenID end)
{
    Token tok = start;
    list<ParsingExpression> exprs;
    
    list<list<ParsingExpression>::iterator> identifiers;
    list<list<ParsingExpression>::iterator> strings;
    list<list<ParsingExpression>::iterator> curlybrs;
    list<list<ParsingExpression>::iterator> calls;
    list<list<ParsingExpression>::iterator> addsub;
    list<list<ParsingExpression>::iterator> colons;
    list<list<ParsingExpression>::iterator> commas;

    try
    {
        for (; tok.id != end; getNextToken(tok))
        {
            switch (tok.id)
            {
                case TOK_OPENCURLYBR: {
                    vector<unique_ptr<const Statement>> stv;
                    
                    BlockStmtStream blockss(lexp);
                    unique_ptr<const Statement> blockstp;
                    while (blockss.getNextStatement(blockstp))
                        stv.push_back(std::move(blockstp));

                    addExpr(exprs, tok, make_unique<CurlyBrExpr>(tok, std::move(stv)), &curlybrs);
                }
                break;

                case TOK_OPENSQBR: {
                    unique_ptr<Expression> exprp;
                    if (!getNextToken(tok)) throw UnexpectedTokenException(tok);
                    exprp = getExpression(tok, TOK_CLOSESQBR);

                    unique_ptr<ArrayExpr> arrayp;
                    if (astType(exprp, ArrayExpr)) {
                        arrayp = moveCast<ArrayExpr>(exprp);
                    } else {
                        vector<unique_ptr<const Expression>> exprv;
                        exprv.push_back(std::move(exprp));
                        arrayp = make_unique<ArrayExpr>(tok, std::move(exprv));
                    }

                    addExpr(exprs, tok, std::move(arrayp));
                }
                break;

                case TOK_OPENPAREN: {
                    unique_ptr<Expression> parenexprp;
                    parenexprp = getExpression(tok, TOK_CLOSEPAREN);
                    addExpr(exprs, tok, std::move(parenexprp));
                }
                break;
                
                case TOK_IDENTIFIER:
                    addExpr(exprs, tok, &identifiers);
                break;

                case TOK_STRING:
                    addExpr(exprs, tok, &strings);
                break;

                case TOK_CALL:
                    addExpr(exprs, tok, &calls);
                break;

                case TOK_PLUS:
                    addExpr(exprs, tok, &addsub);
                break;
                
                case TOK_COLON:
                    addExpr(exprs, tok, &colons);
                break;

                case TOK_COMMA:
                    addExpr(exprs, tok, &commas);
                break;

                case TOK_UNKNOWN:
                    throw UnknownTokenException(tok);
                break;

                default:
                    throw UnexpectedTokenException(tok);
                break;
            }
        }

        exprParse
        (
            exprs,

            identifiers,
            strings,
            curlybrs,
            calls,
            addsub,
            colons,
            commas
        );

        if (exprs.size() != 1) {
            unique_ptr<stack<unique_ptr<Expression>>> errorExprs;
            for (ParsingExpression& p : exprs) errorExprs->push(std::move(p.exprp));
            throw AmbiguousStatementException(std::move(errorExprs));
        }

        unique_ptr<Expression> retval = std::move(exprs.front().exprp);
        exprs.clear(); // Avoids calling ParsingExpression's destructor with an invalid iterator
        return retval;
    }
    catch (exception& e)
    {
        exprs.clear(); // Avoids calling ParsingExpression's destructor with an invalid iterator
        throw;
    }
}

