#include "asttype.hpp"
#include "exceptions.hpp"
#include "expressionparsing.hpp"
#include "ast/expressions.hpp"
#include <forward_list>
#include <typeinfo>

using namespace std;

forward_list<pair<list<list<ParsingExpression>::iterator>::iterator, list<list<ParsingExpression>::iterator>*>> toErase;

ParsingExpression::ParsingExpression
(
        Token token,
        unique_ptr<Expression> exprp,
        list<list<ParsingExpression>::iterator>* itlist
)
: token(token), exprp(std::move(exprp)), itlist(itlist) {}

void eraseExpr(list<ParsingExpression>& exprs, list<ParsingExpression>::iterator it)
{
    if (it->itlist != nullptr)
        toErase.emplace_front(it->it, it->itlist);
    exprs.erase(it);
}

void erasePending()
{
    for (auto i : toErase)
        i.second->erase(i.first);
    toErase.clear();
}

void ctl(void (*f)(list<ParsingExpression>&, list<list<ParsingExpression>::iterator>&), list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& itlist)
{
    try {
        f(exprs, itlist);
        erasePending();
    } catch (exception& e) {
        erasePending();
        throw;
    }
}

template<class T>
void p_parseAtoms(list<list<ParsingExpression>::iterator>& itlist)
{
    for (auto i : itlist) {
        if (!i->exprp)
            i->exprp = make_unique<T>(i->token);
    }
}

template<class T>
void p_parseBinOp(list<ParsingExpression>& exprs, list<ParsingExpression>::iterator i)
{
    if (!i->exprp)
    {
        auto lhs = prev(i), rhs = next(i);

        if (!lhs->exprp) throw UnexpectedTokenException(lhs->token);
        if (!rhs->exprp) throw UnexpectedTokenException(rhs->token);

        i->exprp = make_unique<T>(i->token, std::move(lhs->exprp), std::move(rhs->exprp));

        eraseExpr(exprs, lhs);
        eraseExpr(exprs, rhs);
    }
}

template<class T>
void p_parseBinOps(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& itlist)
{
    for (auto i : itlist)
        p_parseBinOp<T>(exprs, i);
}

void parseVariables(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& identifiers)
{
    p_parseAtoms<VariableExpr>(identifiers);
}

void parseStrings(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& strings)
{
    p_parseAtoms<StringExpr>(strings);
}

void parseDecl(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& identifiers)
{
    for (auto type : identifiers)
    {
        list<ParsingExpression>::iterator var = next(type);
        if (var == exprs.end()) break; // If it's the last ParsingExpression we can quit now because it can't be a declaration
                                       // also, dereferencing var would be an error
        if (!var->exprp) continue;
        if (!astType(var->exprp, VariableExpr)) continue;

        if (!type->exprp) throw UnexpectedTokenException(type->token);

        if (astType(type->exprp, VariableExpr)) {
            unique_ptr<DeclExpr> dep = make_unique<DeclExpr>(var->token, std::move(type->exprp), std::move(var->exprp));
            var->exprp = std::move(dep);

            eraseExpr(exprs, type);
        }
    }
}

void parseCalls(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& calls)
{
    for (auto i : calls)
    {
        if (!i->exprp)
        {
            list<ParsingExpression>::iterator callee = prev(i), args = next(i);

            if (!callee->exprp) throw UnexpectedTokenException(callee->token);

            unique_ptr<FunctionCallExpr> fcep = make_unique<FunctionCallExpr>(i->token, std::move(callee->exprp));
            eraseExpr(exprs, callee);

            //if there's nothing to the right, it's ok, just add no arguments to the function call
            if (!(args == exprs.end() || !args->exprp)) {
                if (!astType(args->exprp, ArrayExpr)) throw UnexpectedTokenException(args->token);
                ArrayExpr* aep = (ArrayExpr*)args->exprp.get();
                for (unique_ptr<const Expression>& arg : aep->expressions) {
                    fcep->args.push_back(std::move(arg));
                }
                eraseExpr(exprs, args);
            }

            i->exprp = std::move(fcep);
        }
    }
}

void parseAddSub(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& addsub)
{
    for (auto i : addsub)
    {
        switch(i->token.id)
        {
            case TOK_PLUS:
                p_parseBinOp<AddExpr>(exprs, i);
            break;
            
            case TOK_MINUS:
            default:
                throw UnexpectedTokenException(i->token);
            break;
        }
    }
}

void parseVariableAssigns(list<ParsingExpression>& exprs, list<list<ParsingExpression>::iterator>& colons)
{
    p_parseBinOps<VariableAssignExpr>(exprs, colons);
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

        unique_ptr<ArrayExpr> arrayp = make_unique<ArrayExpr>(i->token);

        arrayp->expressions.push_back(std::move(lhs->exprp));
        arrayp->expressions.push_back(std::move(rhs->exprp));

        eraseExpr(exprs, lhs);
        eraseExpr(exprs, rhs);

        for (auto j = next(commas.begin()); j != commas.end(); ++j)
        {
            i = *j;
            list<ParsingExpression>::iterator item = next(i);

            if (!item->exprp) throw UnexpectedTokenException(item->token);

            arrayp->expressions.push_back(std::move(item->exprp));

            eraseExpr(exprs, item);

            // All commas are a single expression, so we don't give exprp to other commas
            // So now we have to erase them to not cause an error with uninitialized exprp
            eraseExpr(exprs, i);
        }
        
        commas.front()->exprp = std::move(arrayp);
    }
}

void exprParse
(
    list<ParsingExpression>& exprs,

    list<list<ParsingExpression>::iterator>& identifiers,
    list<list<ParsingExpression>::iterator>& strings,
    list<list<ParsingExpression>::iterator>& calls,
    list<list<ParsingExpression>::iterator>& addsub,
    list<list<ParsingExpression>::iterator>& colons,
    list<list<ParsingExpression>::iterator>& commas
)
{
        ctl(&parseVariables, exprs, identifiers);
        ctl(&parseStrings, exprs, strings);
        ctl(&parseDecl, exprs, identifiers);
        ctl(&parseCalls, exprs, calls);
        ctl(&parseAddSub, exprs, addsub);
        ctl(&parseVariableAssigns, exprs, colons);
        ctl(&parseCommas, exprs, commas);
}

