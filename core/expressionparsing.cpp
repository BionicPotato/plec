#include "exceptions.hpp"
#include "expressionparsing.hpp"
#include "ast/expressions.hpp"
#include <typeinfo>

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
                if (t_a != t_ae) throw UnexpectedTokenException(a->token);
                shared_ptr<ArrayExpr> aep = static_pointer_cast<ArrayExpr>(a->exprp);
                for (shared_ptr<Expression> arg : aep->expressions) {
                    fce->args.push_back(arg);
                }
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
    while (!addsub.empty())
    {
        list<ParsingExpression>::iterator i = addsub.back();

        if (!i->exprp)
        {
            list<ParsingExpression>::iterator lhs = prev(i), rhs = next(i);

            if (!lhs->exprp) throw UnexpectedTokenException(lhs->token);
            if (!rhs->exprp) throw UnexpectedTokenException(rhs->token);

            i->exprp = make_shared<AddExpr>(i->token, lhs->exprp, rhs->exprp);

            exprs.erase(lhs);
            exprs.erase(rhs);
        }
        addsub.pop_back();
    }
}

void parseVariableAssigns(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& colons)
{
    while (!colons.empty())
    {
        list<ParsingExpression>::iterator i = colons.back();

        if (!i->exprp)
        {
            list<ParsingExpression>::iterator var = prev(i), val = next(i);

            if (!var->exprp) throw UnexpectedTokenException(var->token);
            if (!val->exprp) throw UnexpectedTokenException(val->token);

            i->exprp = make_shared<VariableAssignExpr>(i->token, var->exprp, val->exprp);

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

