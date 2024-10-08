#include "token.hpp"
#include "ast/expression.hpp"
#include <list>
#include <stack>
#include <memory>

struct ParsingExpression
{
    Token token;
    std::shared_ptr<Expression> exprp;

    ParsingExpression(Token token, std::shared_ptr<Expression> exprp)
        : token(token), exprp(exprp) {}
};

void parseVariables(std::list<ParsingExpression>& exprs, std::stack<std::list<ParsingExpression>::iterator>& identifiers);
void parseStrings(std::list<ParsingExpression>& exprs, std::stack<std::list<ParsingExpression>::iterator>& strings);
void parseCalls(std::list<ParsingExpression>& exprs, std::stack<std::list<ParsingExpression>::iterator>& calls);
void parseAddSub(std::list<ParsingExpression>& exprs, std::stack<std::list<ParsingExpression>::iterator>& addsub);
void parseVariableAssigns(std::list<ParsingExpression>& exprs, std::stack<std::list<ParsingExpression>::iterator>& colons);

