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
                    unique_ptr<BlockExpr> blockp = make_unique<BlockExpr>(tok);
                    BlockExpr* blockrp = blockp.get();
                    exprs.emplace_back(tok, std::move(blockp), nullptr);
                    BlockStmtStream blockss(lexp);
                    unique_ptr<const Statement> blockstp;
                    while (blockss.getNextStatement(blockstp))
                        blockrp->statements.push_back(std::move(blockstp));
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
                        arrayp = make_unique<ArrayExpr>(tok);
                        arrayp->expressions.push_back(std::move(exprp));
                    }

                    exprs.emplace_back(tok, std::move(arrayp), nullptr);
                }
                break;

                case TOK_OPENPAREN: {
                    unique_ptr<Expression> parenexprp;
                    parenexprp = getExpression(tok, TOK_CLOSEPAREN);
                    exprs.emplace_back(parenexprp->token, std::move(parenexprp), nullptr);
                }
                break;
                
                case TOK_IDENTIFIER:
                    exprs.emplace_back(tok, unique_ptr<Expression>(nullptr), &identifiers);
                    identifiers.push_back(prev(exprs.end()));
                    exprs.back().it = prev(identifiers.end());
                break;

                case TOK_STRING:
                    exprs.emplace_back(tok, unique_ptr<Expression>(nullptr), &strings);
                    strings.push_back(prev(exprs.end()));
                    exprs.back().it = prev(strings.end());
                break;

                case TOK_CALL:
                    exprs.emplace_back(tok, unique_ptr<Expression>(nullptr), &calls);
                    calls.push_back(prev(exprs.end()));
                    exprs.back().it = prev(calls.end());
                break;

                case TOK_PLUS:
                    exprs.emplace_back(tok, unique_ptr<Expression>(nullptr), &addsub);
                    addsub.push_back(prev(exprs.end()));
                    exprs.back().it = prev(addsub.end());
                break;
                
                case TOK_COLON:
                    exprs.emplace_back(tok, unique_ptr<Expression>(nullptr), &colons);
                    colons.push_back(prev(exprs.end()));
                    exprs.back().it = prev(colons.end());
                break;

                case TOK_COMMA:
                    exprs.emplace_back(tok, unique_ptr<Expression>(nullptr), &commas);
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

