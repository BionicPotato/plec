#include "exceptions.hpp"
#include "expressionparsing.hpp"
#include "ast/expressions.hpp"

using namespace std;

void parseVariables(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& identifiers)
{
    while (!identifiers.empty()) {
        if (!identifiers.back()->exprp)
            identifiers.back()->exprp = make_shared<VariableExpr>(identifiers.back()->token);
        identifiers.pop_back();
    }
}

void parseStrings(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& strings)
{
    while (!strings.empty()) {
        if (!strings.back()->exprp)
            strings.back()->exprp = make_shared<StringExpr>(strings.back()->token);
        strings.pop_back();
    }
}

// The FunctionCallExpr's "args" will be a null-pointer if the function is called with no arguments
// To check if a function has been called with no arguments, use:
//      if (!functionCall.args)
// and not:
//      if (functionCall.args.expressions.empty())
void parseCalls(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& calls)
{
    while (!calls.empty()) {
        list<ParsingExpression>::iterator i = calls.back();
        if (!i->exprp) {
            shared_ptr<FunctionCallExpr> fce = make_shared<FunctionCallExpr>(i->token);
            list<ParsingExpression>::iterator c = i, a = i;
            c--; a++;
            if (!c->exprp) throw UnexpectedTokenException(c->token);
            shared_ptr<Expression> callee = c->exprp;
            //if there's nothing to the right, it's ok, just add no arguments to the function call
            if (!(a == exprs.end() || !a->exprp)) {
                const Expression* _a = a->exprp.get();
                const type_info& t_a = typeid(*_a);
                const type_info& t_ae = typeid(ArrayExpr);
                if (t_a != t_ae)
                    throw UnexpectedTokenException(a->token);
                fce->args = static_pointer_cast<ArrayExpr>(a->exprp);
                exprs.erase(a);
            }
            fce->callee = callee;
            i->exprp = fce;
            exprs.erase(c);
        }
        calls.pop_back();
    }
}

void parseAddSub(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& addsub)
{
    while (!addsub.empty()) {
        list<ParsingExpression>::iterator i = addsub.back();
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
        addsub.pop_back();
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
void parseVariableAssigns(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& colons)
{
    while (!colons.empty()) {
        list<ParsingExpression>::iterator i = colons.back();
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
        colons.pop_back();
    }
}

void parseCommas(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& commas)
{
    if (!commas.empty())
    {
        list<ParsingExpression>::iterator i = commas.front();
        list<ParsingExpression>::iterator lhs = prev(i);
        list<ParsingExpression>::iterator rhs = next(i);

        if (!lhs->exprp) throw UnexpectedTokenException(lhs->token);
        if (!rhs->exprp) throw UnexpectedTokenException(rhs->token);

        shared_ptr<ArrayExpr> arrayp = make_shared<ArrayExpr>(i->token);

        arrayp->expressions.push_back(lhs->exprp);
        arrayp->expressions.push_back(rhs->exprp);

        exprs.erase(lhs);
        exprs.erase(rhs);

        i->exprp = arrayp;

        commas.pop_front();

        while (!commas.empty())
        {
            list<ParsingExpression>::iterator j = commas.front();
            list<ParsingExpression>::iterator item = next(j);

            if (!rhs->exprp) throw UnexpectedTokenException(item->token);

            arrayp->expressions.push_back(item->exprp);

            exprs.erase(item);
            exprs.erase(j); // We're not giving j an exprp because the ParsingExpression representing this array is already in i
                            // So now we have to erase it to not cause an error with uninitialized exprp

            commas.pop_front();
        }
    }
}

