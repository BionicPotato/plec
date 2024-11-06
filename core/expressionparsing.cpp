#include "asttype.hpp"
#include "exceptions.hpp"
#include "expressionparsing.hpp"
#include "ast/expressions.hpp"
#include <forward_list>
#include <typeinfo>

using namespace std;

ParsingExpression::ParsingExpression
(
        Token token,
        shared_ptr<Expression> exprp,
        list<list<ParsingExpression>::iterator>* itlist
)
: token(token), exprp(exprp), itlist(itlist) {}

ParsingExpression::~ParsingExpression()
{
    if (itlist != nullptr)
        itlist->erase(it);
}

void parseVariables(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& identifiers)
{
    for (auto i : identifiers) {
        if (!i->exprp)
            i->exprp = make_shared<VariableExpr>(i->token);
    }
}

void parseStrings(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& strings)
{
    for (auto i : strings) {
        if (!i->exprp)
            i->exprp = make_shared<StringExpr>(i->token);
    }
}

void parseDecl(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& identifiers)
{
    forward_list<list<ParsingExpression>::iterator> toErase;
    for (auto type : identifiers)
    {
        list<ParsingExpression>::iterator var = next(type);
        if (var == exprs.end()) return; // If it's the last ParsingExpression we can quit now because it can't be a declaration
                                        // also, dereferencing var would be an error
        if (!var->exprp) continue;
        if (!astType(var->exprp, VariableExpr)) continue;

        if (!type->exprp) throw UnexpectedTokenException(type->token);

        if (astType(type->exprp, VariableExpr)) {
            shared_ptr<DeclExpr> dep = make_shared<DeclExpr>(var->token, type->exprp, var->exprp);
            var->exprp = dep;

            toErase.push_front(type);
        }
    }
    for (auto j : toErase)
        exprs.erase(j);
}

void parseCalls(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& calls)
{
    for (auto i : calls)
    {
        if (!i->exprp)
        {
            list<ParsingExpression>::iterator callee = prev(i), args = next(i);

            if (!callee->exprp) throw UnexpectedTokenException(callee->token);

            shared_ptr<FunctionCallExpr> fcep = make_shared<FunctionCallExpr>(i->token, callee->exprp);
            
            //if there's nothing to the right, it's ok, just add no arguments to the function call
            if (!(args == exprs.end() || !args->exprp)) {
                const Expression* _a = args->exprp.get();
                const type_info& t_a = typeid(*_a);
                const type_info& t_ae = typeid(ArrayExpr);
                if (t_a != t_ae) throw UnexpectedTokenException(args->token);
                shared_ptr<ArrayExpr> aep = static_pointer_cast<ArrayExpr>(args->exprp);
                for (shared_ptr<Expression> arg : aep->expressions) {
                    fcep->args.push_back(arg);
                }
                exprs.erase(args);
            }

            i->exprp = fcep;

            exprs.erase(callee);
        }
    }
}

void parseAddSub(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& addsub)
{
    for (auto i : addsub)
    {
        if (!i->exprp)
        {
            list<ParsingExpression>::iterator lhs = prev(i), rhs = next(i);

            if (!lhs->exprp) throw UnexpectedTokenException(lhs->token);
            if (!rhs->exprp) throw UnexpectedTokenException(rhs->token);

            i->exprp = make_shared<AddExpr>(i->token, lhs->exprp, rhs->exprp);

            exprs.erase(lhs);
            exprs.erase(rhs);
        }
    }
}

void parseVariableAssigns(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& colons)
{
    for (auto i : colons)
    {
        if (!i->exprp)
        {
            list<ParsingExpression>::iterator var = prev(i), val = next(i);

            if (!var->exprp) throw UnexpectedTokenException(var->token);
            if (!val->exprp) throw UnexpectedTokenException(val->token);

            i->exprp = make_shared<VariableAssignExpr>(i->token, var->exprp, val->exprp);

            exprs.erase(var);
            exprs.erase(val);
        }
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

        forward_list<list<ParsingExpression>::iterator> toErase;
        for (auto j = next(commas.begin()); j != commas.end(); ++j)
        {
            i = *j;
            list<ParsingExpression>::iterator item = next(i);

            if (!item->exprp) throw UnexpectedTokenException(item->token);

            arrayp->expressions.push_back(item->exprp);

            exprs.erase(item);
            toErase.push_front(i);
        }
        // All commas are a single expression, so we don't give exprp to other commas
        // So now we have to erase them to not cause an error with uninitialized exprp
        for (auto j : toErase)
            exprs.erase(j);
    }
}

