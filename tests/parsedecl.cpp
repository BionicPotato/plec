#include "test.hpp"
#include "../core/asttype.hpp"
#include "../core/expressionparsing.hpp"
#include "../core/ast/expressions.hpp"
#include <list>

using namespace std;

int main()
{
    Token tokStr = {TOK_IDENTIFIER, "Str", "parsedecl.ple", 1, 1};
    Token tokMessage = {TOK_IDENTIFIER, "message", "parsedecl.ple", 1, 5};
    Token tokColon = {TOK_COLON, ":", "parsedecl.ple", 1, 7};
    Token tokHello = {TOK_STRING, "\"Hello, world!\"", "parsedecl.ple", 1, 9};
    Token tokComma = {TOK_COMMA, ",", "parsedecl.ple", 1, 17};
    Token tokInt = {TOK_IDENTIFIER, "Int", "parsedecl.ple", 2, 1};
    Token tokX = {TOK_IDENTIFIER, "x", "parsedecl.ple", 2, 5};

    list<list<ParsingExpression>::iterator> identifiers; 
    list<ParsingExpression> exprs;
    exprs.emplace_back(tokStr, nullptr, &identifiers);
    exprs.back().it = identifiers.end();
    exprs.emplace_back(tokMessage, nullptr, &identifiers);
    exprs.back().it = identifiers.end();
    exprs.emplace_back(tokColon, nullptr, nullptr);
    exprs.emplace_back(tokHello, nullptr, nullptr);
    exprs.emplace_back(tokComma, nullptr, nullptr);
    exprs.emplace_back(tokInt, nullptr, &identifiers);
    exprs.back().it = identifiers.end();
    exprs.emplace_back(tokX, nullptr, &identifiers);
    exprs.back().it = identifiers.end();
    identifiers = {exprs.begin(), next(exprs.begin()), prev(prev(exprs.end())), prev(exprs.end())};
    exprs.front().it = identifiers.begin();
    next(exprs.begin())->it = next(identifiers.begin());
    prev(prev(exprs.end()))->it = prev(prev(identifiers.end()));
    exprs.back().it = prev(identifiers.end());

    parseVariables(exprs, identifiers);
    parseDecl(exprs, identifiers);

    require(
        exprs.size() == 5,
        "Expression list's size is not 5");

    list<ParsingExpression>::iterator i = exprs.begin();
    require(
        astType(i->exprp, DeclExpr),
        "First expression is not DeclExpr");
    shared_ptr<DeclExpr> dep =
        static_pointer_cast<DeclExpr>(i->exprp);
    require(
        astType(dep->lhs, VariableExpr),
        "First expression's LHS is not VariableExpr");
    require(
        dep->lhs->token.content == "Str",
        "First expression's LHS is not 'Str'");
    require(
        astType(dep->rhs, VariableExpr),
        "First expression's RHS is not VariableExpr");
    require(
        dep->rhs->token.content == "message",
        "First expression's RHS is not 'message'");
    
    i++;
    require(
        i->exprp == nullptr,
        "Second expression has been initialized");

    i++;
    require(
        i->exprp == nullptr,
        "Third expression has been initialized");

    i++;
    require(
        i->exprp == nullptr,
        "Fourth expression has been initialized");

    i++;
    require(
        astType(i->exprp, DeclExpr),
        "Fifth expression is not DeclExpr");
    dep = static_pointer_cast<DeclExpr>(i->exprp);
    require(
        astType(dep->lhs, VariableExpr),
        "Fifth expression's LHS is not VariableExpr");
    require(
        dep->lhs->token.content == "Int",
        "Fifth expression's LHS is not 'Int'");
    require(
        astType(dep->rhs, VariableExpr),
        "Fifth expression's RHS is not VariableExpr");
    require(
        dep->rhs->token.content == "x",
        "Fifth expression's RHS is not 'x'");

    i++;
    require(
        i == exprs.end(),
        "Expression list contains more expressions");
}
