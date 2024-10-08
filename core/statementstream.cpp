#include "statementstream.hpp"
#include "ast/blockexpr.hpp"
#include "ast/program.hpp"
#include "ast/statement.hpp"
#include "stmtstreams/block.hpp"
#include "expressionparsing.hpp"
#include "token.hpp"
#include "ast/expression.hpp"
#include "ast/functioncallexpr.hpp"
#include "ast/operatorexpression.hpp"
#include "ast/programstmt.hpp"
#include "ast/addexpr.hpp"
#include "ast/stringexpr.hpp"
#include "ast/variableexpr.hpp"
#include "ast/variableassignexpr.hpp"
#include "exceptions.hpp"
#include "operators.hpp"
#include "tokenid.hpp"
#include <deque>
#include <list>
#include <functional>
#include <stack>
#include <memory>

using namespace std;

StatementStream::StatementStream(shared_ptr<Lexer> lexp): lexp(lexp), filename(lexp->filename) {}

bool StatementStream::getNextStatement(shared_ptr<Statement>& stp)
{
    Token tok;
    if (!getNextToken(tok)) return false;
    if (checkProgramStmt(tok, stp)) return true;
    else stp = getExpression(tok, TOK_SEMICOLON);
    return true;
}

shared_ptr<Expression> StatementStream::getExpression(const Token& start, TokenID end)
{
    Token tok = start;
    list<ParsingExpression> exprs;
    
    stack<list<ParsingExpression>::iterator> identifiers;
    stack<list<ParsingExpression>::iterator> strings;
    stack<list<ParsingExpression>::iterator> calls;
    stack<list<ParsingExpression>::iterator> addsub;
    stack<list<ParsingExpression>::iterator> colons;

    for (; tok.id != end; getNextToken(tok))
    {
        switch (tok.id)
        {
            case TOK_OPENCURLYBR: {
                shared_ptr<BlockExpr> blockp = make_shared<BlockExpr>(tok);
                exprs.emplace_back(tok, blockp);
                BlockStmtStream blockss(lexp);
                shared_ptr<Statement> blockstp;
                while (blockss.getNextStatement(blockstp)) {
                    blockp->statements.push_back(blockstp);
                }
            }
            break;

            //TODO: add Square Bracket Expression and make function calls require it and not any
            //other type of expression (also, ExpressionStream? i don't think it's needed)
            case TOK_OPENSQBR: {
                shared_ptr<Expression> sqbrexprp;
                sqbrexprp = getExpression(tok, TOK_CLOSESQBR);
                exprs.emplace_back(sqbrexprp->token, sqbrexprp);
            }
            break;

            case TOK_OPENPAREN: {
                shared_ptr<Expression> parenexprp;
                parenexprp = getExpression(tok, TOK_CLOSEPAREN);
                exprs.emplace_back(parenexprp->token, parenexprp);
            }
            break;
            
            case TOK_IDENTIFIER:
                exprs.emplace_back(tok, shared_ptr<Expression>(nullptr));
                identifiers.push(prev(exprs.end()));
            break;

            case TOK_STRING:
                exprs.emplace_back(tok, shared_ptr<Expression>(nullptr));
                strings.push(prev(exprs.end()));
            break;

            case TOK_CALL:
                exprs.emplace_back(tok, shared_ptr<Expression>(nullptr));
                calls.push(prev(exprs.end()));
            break;

            case TOK_PLUS:
                exprs.emplace_back(tok, shared_ptr<Expression>(nullptr));
                addsub.push(prev(exprs.end()));
            break;
            
            case TOK_COLON:
                exprs.emplace_back(tok, shared_ptr<Expression>(nullptr));
                colons.push(prev(exprs.end()));
            break;

            default:
            case TOK_UNKNOWN:
                throw UnknownTokenException(tok);
            break;
        }
    }

    parseVariables(exprs, identifiers);
    parseStrings(exprs, strings);
    parseCalls(exprs, calls);
    parseAddSub(exprs, addsub);
    parseVariableAssigns(exprs, colons);

    if (exprs.size() != 1) {
        stack<shared_ptr<Expression>> errorExprs;
        for (ParsingExpression p : exprs) errorExprs.push(p.exprp);
        throw AmbiguousStatementException(errorExprs);
    }

    return exprs.front().exprp;
}

