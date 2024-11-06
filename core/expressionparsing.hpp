#pragma once

#include "token.hpp"
#include "ast/expression.hpp"
#include <list>
#include <memory>

struct ParsingExpression
{
    Token token;
    std::shared_ptr<Expression> exprp;
    std::list<std::list<ParsingExpression>::iterator>*itlist;
    std::list<std::list<ParsingExpression>::iterator>::iterator it;

    ParsingExpression(Token token, std::shared_ptr<Expression> exprp, std::list<std::list<ParsingExpression>::iterator>* itlist);
    ~ParsingExpression();
};

void parseVariables(std::list<ParsingExpression>& exprs, std::list<std::list<ParsingExpression>::iterator>& identifiers);
void parseStrings(std::list<ParsingExpression>& exprs, std::list<std::list<ParsingExpression>::iterator>& strings);
void parseDecl(std::list<ParsingExpression>& exprs, std::list<std::list<ParsingExpression>::iterator>& identifiers);
void parseCalls(std::list<ParsingExpression>& exprs, std::list<std::list<ParsingExpression>::iterator>& calls);
void parseAddSub(std::list<ParsingExpression>& exprs, std::list<std::list<ParsingExpression>::iterator>& addsub);
void parseVariableAssigns(std::list<ParsingExpression>& exprs, std::list<std::list<ParsingExpression>::iterator>& colons);
void parseCommas(std::list<ParsingExpression>& exprs, std::list<std::list<ParsingExpression>::iterator>& commas);

