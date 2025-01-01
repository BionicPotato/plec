#pragma once

#include "token.hpp"
#include "ast/expression.hpp"
#include <list>
#include <memory>

struct ParsingExpression
{
    Token token;
    std::unique_ptr<Expression> exprp;
    std::list<std::list<ParsingExpression>::iterator>* itlist;
    std::list<std::list<ParsingExpression>::iterator>::iterator it;

    ParsingExpression(Token token, std::unique_ptr<Expression> exprp, std::list<std::list<ParsingExpression>::iterator>* itlist);
};

void addExpr(std::list<ParsingExpression>& exprs, Token token, std::unique_ptr<Expression> exprp);
void addExpr(std::list<ParsingExpression>& exprs, Token token, std::list<std::list<ParsingExpression>::iterator>* itlist);
void addExpr(std::list<ParsingExpression>& exprs, Token token, std::unique_ptr<Expression> exprp, std::list<std::list<ParsingExpression>::iterator>* itlist);

void exprParse
(
    std::list<ParsingExpression>& exprs,

    std::list<std::list<ParsingExpression>::iterator>& identifiers,
    std::list<std::list<ParsingExpression>::iterator>& strings,
    std::list<std::list<ParsingExpression>::iterator>& curlybrs,
    std::list<std::list<ParsingExpression>::iterator>& calls,
    std::list<std::list<ParsingExpression>::iterator>& addsub,
    std::list<std::list<ParsingExpression>::iterator>& colons,
    std::list<std::list<ParsingExpression>::iterator>& commas
);

