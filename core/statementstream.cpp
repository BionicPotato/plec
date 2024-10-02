#include "statementstream.hpp"
#include "ast/blockexpr.hpp"
#include "ast/program.hpp"
#include "ast/statement.hpp"
#include "stmtstreams/block.hpp"
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
#include <functional>
#include <stack>
#include <memory>

using namespace std;

StatementStream::StatementStream(shared_ptr<Lexer> lexp): lexp(lexp), filename(lexp->filename) {}

bool StatementStream::getNextStatement(shared_ptr<Statement>& stp)
{
    Token tok;
    deque<Token> rpntok;
    stack<Token> optok;
    stack<shared_ptr<Expression>> exprs;
    stack<shared_ptr<BlockExpr>> blocks;

    if (!getNextToken(tok)) return false;

    if (checkProgramStmt(tok, stp)) return true;

    else for (; tok.id != TOK_SEMICOLON; getNextToken(tok))
    {
        switch (tok.id)
        {
            case TOK_OPENCURLYBR: {
                rpntok.push_back(tok);
                shared_ptr<BlockExpr> block = make_shared<BlockExpr>(tok);
                blocks.push(block);
                BlockStmtStream blockss(lexp);
                shared_ptr<Statement> blockstp;
                while (blockss.getNextStatement(blockstp)) {
                    block->statements.push_back(blockstp);
                }
            }
            break;

            case TOK_CLOSECURLYBR: return false;

            case TOK_IDENTIFIER:
            case TOK_STRING:
                rpntok.push_back(tok);
            break;
            
            case TOK_COLON:
            case TOK_CALL:
            case TOK_PLUS:
                while (
                    !optok.empty() && optok.top().id != TOK_OPENPAREN
                    && (getPrecedence(optok.top().id) > getPrecedence(tok.id)
                        || (getPrecedence(optok.top().id) == getPrecedence(tok.id) && isLeftAssociative(tok.id))
                    )
                ) {
                    Token t = optok.top();
                    rpntok.push_back(t);
                    optok.pop();
                }
            case TOK_OPENPAREN:
                optok.push(tok);
            break;

            case TOK_CLOSEPAREN:
                while (optok.top().id != TOK_OPENPAREN) {
                    if (optok.empty()) throw UnexpectedTokenException(tok);
                    Token t = optok.top();
                    rpntok.push_back(t);
                    optok.pop();
                }
                if (optok.top().id != TOK_OPENPAREN) throw UnexpectedTokenException(tok);
                optok.pop();
            break;
            
            default:
            case TOK_UNKNOWN:
                throw UnknownTokenException(tok);
        }
    }
    while (!optok.empty()) {
        if (optok.top().id == TOK_OPENPAREN) throw UnexpectedTokenException(optok.top());
        Token t = optok.top();
        rpntok.push_back(t);
        optok.pop();
    }

    static shared_ptr<OperatorExpression> op;
    for (Token tok : rpntok)
    {
        switch (tok.id)
        {
            case TOK_IDENTIFIER:
                exprs.push(make_shared<VariableExpr>(tok));
            break;

            case TOK_STRING:
                exprs.push(make_shared<StringExpr>(tok));
            break;

            case TOK_OPENCURLYBR:
                exprs.push(blocks.top());
                blocks.pop();
            break;

            case TOK_CALL: {
                shared_ptr<FunctionCallExpr> fce = make_shared<FunctionCallExpr>(tok);
                if (exprs.size() > 1) {
                    fce->args.push_back(exprs.top());
                    exprs.pop();
                }
                fce->callee = exprs.top();
                exprs.pop();
                exprs.push(fce);
            }
            break;

            case TOK_COLON:
                op = make_shared<VariableAssignExpr>(tok);
            goto LBL_ADDOP;
            case TOK_PLUS:
                op = make_shared<AddExpr>(tok);
            LBL_ADDOP: {
                shared_ptr<Expression> ex2 = exprs.top();
                exprs.pop();
                shared_ptr<Expression> ex1 = exprs.top();
                exprs.pop();
                op->assignOperands(ex1, ex2);
                exprs.push(op);
            }
            break;

            default:
            case TOK_UNKNOWN:
                throw UnknownTokenException(tok);
        }
    }

    if (exprs.size() != 1) throw AmbiguousStatementException(exprs);
    stp = exprs.top();
    return true;
}
