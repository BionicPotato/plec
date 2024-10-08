#include "exceptions.hpp"
#include "expressionparsing.hpp"
#include "ast/expressions.hpp"

using namespace std;

void parseVariables(list<ParsingExpression>& exprs, stack<list<ParsingExpression>::iterator>& identifiers)
{
    while (!identifiers.empty()) {
        if (!identifiers.top()->exprp)
            identifiers.top()->exprp = make_shared<VariableExpr>(identifiers.top()->token);
        identifiers.pop();
    }
}

void parseStrings(list<ParsingExpression>& exprs, stack<list<ParsingExpression>::iterator>& strings)
{
    while (!strings.empty()) {
        if (!strings.top()->exprp)
            strings.top()->exprp = make_shared<StringExpr>(strings.top()->token);
        strings.pop();
    }
}

void parseCalls(list<ParsingExpression>& exprs, stack<list<ParsingExpression>::iterator>& calls)
{
    while (!calls.empty()) {
        list<ParsingExpression>::iterator i = calls.top();
        if (!i->exprp) {
            shared_ptr<FunctionCallExpr> fce = make_shared<FunctionCallExpr>(i->token);
            list<ParsingExpression>::iterator c = i, a = i;
            c--; a++;
            if (!c->exprp) throw UnexpectedTokenException(c->token);
            shared_ptr<Expression> callee = c->exprp;
            //if there's nothing to the right, it's ok, just add no arguments to the function call
            //TODO: when square bracket expression is added, loop through all its expressions and
            //      add them all to the function call's args
            if (!(a == exprs.end() || !a->exprp)) {
                fce->args.push_back(a->exprp);
                exprs.erase(a);
            }
            fce->callee = callee;
            i->exprp = fce;
            exprs.erase(c);
        }
        calls.pop();
    }
}

void parseAddSub(list<ParsingExpression>& exprs, stack<list<ParsingExpression>::iterator>& addsub)
{
    while (!addsub.empty()) {
        list<ParsingExpression>::iterator i = addsub.top();
        if (!i->exprp) {
            shared_ptr<AddExpr> addexprp = make_shared<AddExpr>(i->token);
            list<ParsingExpression>::iterator l = i, r = i;
            l--;
            if (!l->exprp) throw UnexpectedTokenException(l->token);
            shared_ptr<Expression> lhs = l->exprp;
            r++;
            if (!r->exprp) throw UnexpectedTokenException(r->token);
            shared_ptr<Expression> rhs = r->exprp;
            addexprp->assignOperands(lhs, rhs);
            i->exprp = addexprp;
            exprs.erase(l);
            exprs.erase(r);
        }
        addsub.pop();
    }
}

// problem: a + b $ c will parse as (a + b) $ c instead of the intended a + (b $ c)
// however, a $ b + c should parse as a $ (b + c) and not (a $ b) + c
// x : y $ z parse as (x) : (y $ z) (set x to the return value of y)
// x $ y : z pase as (x) $ (y : z) (set y to z, and pass y as a parameter to x)
// unsolvable paradox with current syntax!
//
// redo syntax:
// function calls always take arguments in square brackets: stdout.put $ ["Hello world!"];
// function calls with no arguments stay the same: sayHello $;
// function calls are parsed first, before additions:
//      5 + math.sqrt $ [25] = 5 + (math.sqrt $ [25])
//      math.sqrt $ [25] + 5 = (math.sqrt $ [25]) + 5
//TOK_COLON, TOK_CALL
void parseVariableAssigns(list<ParsingExpression>& exprs, stack<list<ParsingExpression>::iterator>& colons)
{
    while (!colons.empty()) {
        list<ParsingExpression>::iterator i = colons.top();
        if (!i->exprp) {
            shared_ptr<VariableAssignExpr> varaexprp = make_shared<VariableAssignExpr>(i->token);
            list<ParsingExpression>::iterator var = i, val = i;
            var--;
            if (!var->exprp) throw UnexpectedTokenException(var->token);
            shared_ptr<Expression> varp = var->exprp;
            val++;
            if (!val->exprp) throw UnexpectedTokenException(val->token);
            shared_ptr<Expression> valp = val->exprp;
            varaexprp->assignOperands(varp, valp);
            i->exprp = varaexprp;
            exprs.erase(var);
            exprs.erase(val);
        }
        colons.pop();
    }
}


