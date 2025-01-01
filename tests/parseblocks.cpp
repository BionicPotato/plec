#include "test.hpp"
#include "../core/asttype.hpp"
#include "../core/ast/expressions.hpp"
#include "../core/expressionparsing.hpp"
#include <list>

using namespace std;

void ctl(void (*f)(list<ParsingExpression>&, list<list<ParsingExpression>::iterator>&), list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& itlist);
void parseBlocks(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& curlybrs);

int main()
{
    Token tokOpenCurly0 = {TOK_OPENCURLYBR, "{", "parseblocks.ple", 1, 1};
    Token tokCloseCurly0 = {TOK_CLOSECURLYBR, "}", "parseblocks.ple", 1, 2};
    Token tokOpenSq = {TOK_OPENSQBR, "[", "parseblocks.ple", 1, 3};
    Token tokCloseSq = {TOK_CLOSESQBR, "]", "parseblocks.ple", 1, 4};
    Token tokOpenCurly1 = {TOK_OPENCURLYBR, "{", "parseblocks.ple", 1, 5};
    Token tokCloseCurly1 = {TOK_CLOSECURLYBR, "}", "parseblocks.ple", 1, 6};

    list<ParsingExpression> exprs;
    list<list<ParsingExpression>::iterator> curlybrs;
    addExpr(exprs, tokOpenCurly0, make_unique<CurlyBrExpr>(tokOpenCurly0, vector<unique_ptr<const Statement>>()), &curlybrs);
    addExpr(exprs, tokOpenSq, make_unique<ArrayExpr>(tokOpenSq, vector<unique_ptr<const Expression>>()));
    addExpr(exprs, tokOpenCurly1, make_unique<CurlyBrExpr>(tokOpenCurly1, vector<unique_ptr<const Statement>>()), &curlybrs);

    ctl(&parseBlocks, exprs, curlybrs);

    require(
        exprs.size() == 2,
        "Expression list's size is not 5");

    list<ParsingExpression>::iterator i = exprs.begin();
    require(
        i->exprp != nullptr,
        "First expression has not been initialized");
    require(
        astType(i->exprp, BlockExpr),
        "First expression is not BlockExpr");
    const BlockExpr* bep = static_cast<BlockExpr*>(i->exprp.get());
    require(
        bep->dataBlock != nullptr,
        "First expression's data block has not been initialized");
    require(
        bep->dataBlock->expressions.size() == 0,
        "First expression's data block has expressions");
    require(
        bep->statementBlock != nullptr,
        "First expression's statement block has not been initialized");
    require(
        bep->statementBlock->statements.size() == 0,
        "First expression's statement block has statements");

    ++i;
    require(
        i->exprp != nullptr,
        "Second expression has not been initialized");
    require(
        astType(i->exprp, BlockExpr),
        "Second expression is not BlockExpr");
    bep = static_cast<BlockExpr*>(i->exprp.get());
    require(
        bep->dataBlock != nullptr,
        "Second expression's data block has not been initialized");
    require(
        bep->dataBlock->expressions.size() == 0,
        "Second expression's data block has expressions");
    require(
        bep->statementBlock != nullptr,
        "Second expression's statement block has not been initialized");
    require(
        bep->statementBlock->statements.size() == 0,
        "Second expression's statement block has statements");

    return 0;
}
