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

bool StatementStream::getNextStatement(shared_ptr<Statement>& stp)
{
    Token tok;
    if (!getNextToken(tok)) return false;
    if (checkCurlyBr(tok)) return false;
    if (checkProgramStmt(tok, stp)) return true;
    else stp = getExpression(tok, TOK_SEMICOLON);
    return true;
}

shared_ptr<Expression> StatementStream::getExpression(const Token& start, TokenID end)
{
    Token tok = start;
    list<ParsingExpression> exprs;
    
    list<list<ParsingExpression>::iterator> identifiers;
    list<list<ParsingExpression>::iterator> strings;
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
                    shared_ptr<BlockExpr> blockp = make_shared<BlockExpr>(tok);
                    exprs.emplace_back(tok, blockp, nullptr);
                    BlockStmtStream blockss(lexp);
                    shared_ptr<Statement> blockstp;
                    while (blockss.getNextStatement(blockstp))
                        blockp->statements.push_back(blockstp);
                }
                break;

                case TOK_OPENSQBR: {
                    shared_ptr<Expression> exprp;
                    if (!getNextToken(tok)) throw UnexpectedTokenException(tok);
                    exprp = getExpression(tok, TOK_CLOSESQBR);
                    shared_ptr<ArrayExpr> arrayp;
                    const Expression* _e = exprp.get();
                    const type_info& t_e = typeid(*_e);
                    const type_info& t_ae = typeid(ArrayExpr);
                    if (t_e == t_ae) {
                        arrayp = static_pointer_cast<ArrayExpr>(exprp);
                    } else {
                        arrayp = make_shared<ArrayExpr>(tok);
                        arrayp->expressions.push_back(exprp);
                    }
                    exprs.emplace_back(tok, arrayp, nullptr);
                }
                break;

                case TOK_OPENPAREN: {
                    shared_ptr<Expression> parenexprp;
                    parenexprp = getExpression(tok, TOK_CLOSEPAREN);
                    exprs.emplace_back(parenexprp->token, parenexprp, nullptr);
                }
                break;
                
                case TOK_IDENTIFIER:
                    exprs.emplace_back(tok, shared_ptr<Expression>(nullptr), &identifiers);
                    identifiers.push_back(prev(exprs.end()));
                    exprs.back().it = prev(identifiers.end());
                break;

                case TOK_STRING:
                    exprs.emplace_back(tok, shared_ptr<Expression>(nullptr), &strings);
                    strings.push_back(prev(exprs.end()));
                    exprs.back().it = prev(strings.end());
                break;

                case TOK_CALL:
                    exprs.emplace_back(tok, shared_ptr<Expression>(nullptr), &calls);
                    calls.push_back(prev(exprs.end()));
                    exprs.back().it = prev(calls.end());
                break;

                case TOK_PLUS:
                    exprs.emplace_back(tok, shared_ptr<Expression>(nullptr), &addsub);
                    addsub.push_back(prev(exprs.end()));
                    exprs.back().it = prev(addsub.end());
                break;
                
                case TOK_COLON:
                    exprs.emplace_back(tok, shared_ptr<Expression>(nullptr), &colons);
                    colons.push_back(prev(exprs.end()));
                    exprs.back().it = prev(colons.end());
                break;

                case TOK_COMMA:
                    exprs.emplace_back(tok, shared_ptr<Expression>(nullptr), &commas);
                    commas.push_back(prev(exprs.end()));
                    exprs.back().it = prev(commas.end());
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
            calls,
            addsub,
            colons,
            commas
        );

        if (exprs.size() != 1) {
            shared_ptr<stack<shared_ptr<Expression>>> errorExprs;
            for (ParsingExpression p : exprs) errorExprs->push(p.exprp);
            throw AmbiguousStatementException(errorExprs);
        }

        shared_ptr<Expression> retval = exprs.front().exprp;
        exprs.clear(); // Avoids calling ParsingExpression's destructor with an invalid iterator
        return retval;
    }
    catch (exception& e)
    {
        exprs.clear(); // Avoids calling ParsingExpression's destructor with an invalid iterator
        throw;
    }
}

