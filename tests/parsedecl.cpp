#include "test.hpp"
#include "../core/asttype.hpp"
#include "../core/expressionparsing.hpp"
#include "../core/ast/expressions.hpp"
#include <list>

using namespace std;

int main()
{
    list<ParsingExpression> exprs;
    exprs.push_back({{TOK_IDENTIFIER, "Str", "parsedecl.ple", 1, 1}, nullptr});
    exprs.push_back({{TOK_IDENTIFIER, "message", "parsedecl.ple", 1, 5}, nullptr});
    exprs.push_back({{TOK_COLON, ":", "parsedecl.ple", 1, 7}, nullptr});
    exprs.push_back({{TOK_STRING, "\"Hello, world!\"", "parsedecl.ple", 1, 9}, nullptr});
    exprs.push_back({{TOK_COMMA, ",", "parsedecl.ple", 1, 17}, nullptr});
    exprs.push_back({{TOK_IDENTIFIER, "Int", "parsedecl.ple", 2, 1}, nullptr});
    exprs.push_back({{TOK_IDENTIFIER, "x", "parsedecl.ple", 2, 5}, nullptr});
    list<list<ParsingExpression>::iterator> identifiers =
    {exprs.begin(), next(exprs.begin()), prev(prev(exprs.end())), prev(exprs.end())};

    auto varIdentifiers = identifiers;
    parseVariables(exprs, varIdentifiers);
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
