#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include "cst.hpp"
#include "cstnode.hpp"
#include "exceptions/unexpectedtoken.hpp"
#include "tokenid.hpp"
#include "operators.hpp"

using namespace std;

bool CST::addNode(Token tok)
{
    if (tok.id == TOK_EOF) return false;

    CSTNode node;
    
    node.enclosing =
        (tok.id >= TOK_OPENPAREN && tok.id <= TOK_OPENPAREN + 0xf)
        ? ((tok.id % 2 == 0) ? 1 : -1)
        : 0;
    pair<uint8_t, uint8_t> valency = getValency(tok.id);
    node.lhs = valency.first;
    node.rhs = valency.second;
    node.precedence = getPrecedence(tok.id);

    node.token = tok;
    nodes.emplace_back(node);

    return true;
}

void CST::parse()
{
    stack<CSTNode*> enclStack;

    for (CSTNode& node : nodes)
    {
        if (node.enclosing == -1) {
            if (node.token.id != enclStack.top()->token.id + 1)
                throw UnexpectedTokenException(node.token);
            enclStack.pop();
        } else {
            if (enclStack.empty()) topNodes.emplace_back(&node);
            else enclStack.top()->RHSChildren.emplace_back(&node);
            if (node.enclosing == 1) enclStack.push(&node);
        }
    }

    parseBlocks(topNodes);
    //parseFlowControl(topNodes);
    //parseSemicolons(topNodes);
    parseStatements(topNodes);
    parseTypes(topNodes);
    parseOperators(topNodes);
}

void CST::parseBlocks(list<CSTNode*>& nodeList)
{
    for (CSTNode* nodeptr : nodeList) {
        if (!nodeptr->LHSChildren.empty()) parseBlocks(nodeptr->LHSChildren);
        if (!nodeptr->RHSChildren.empty()) parseBlocks(nodeptr->RHSChildren);
    }

    for (list<CSTNode*>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
        if ((*it)->token.id == TOK_OPENSQBR) {
            list<CSTNode*>::iterator nextIt = next(it);
            if ((*nextIt)->token.id == TOK_OPENCURLYBR) {
                (*nextIt)->LHSChildren.emplace_front(*it);
                nodeList.erase(it);
                it = nextIt;
            }
        }
    }
}

void CST::parseStatements(std::list<CSTNode*>& nodeList)
{
    for (CSTNode* nodeptr : nodeList) {
        if (!nodeptr->LHSChildren.empty()) parseStatements(nodeptr->LHSChildren);
        if (!nodeptr->RHSChildren.empty()) parseStatements(nodeptr->RHSChildren);
    }

    for (list<CSTNode*>::iterator fc = nodeList.begin(); fc != nodeList.end(); fc++)
    {
        switch ((*fc)->token.id)
        {
            case TOK_WHEN:
            case TOK_IF:
            case TOK_WHILE:
            case TOK_REPEAT:
                for (list<CSTNode*>::iterator it = next(fc);;) {
                    if ((*it)->token.id == TOK_OPENCURLYBR) {
                        (*fc)->RHSChildren.emplace_back(*it);
                        nodeList.erase(it);
                        break;
                    } else if ((*it)->token.id == TOK_THEN || (*it)->token.id == TOK_DO) {
                        break;
                    } else {
                        (*fc)->LHSChildren.emplace_back(*it);
                        list<CSTNode*>::iterator erased = it;
                        it++;
                        nodeList.erase(erased);
                    }
                }
                break;
            
            case TOK_DO:
            case TOK_THEN:
            case TOK_ELSE:
            {
                list<CSTNode*>::iterator it = next(fc);
                if ((*it)->token.id == TOK_OPENCURLYBR) {
                    (*fc)->RHSChildren.emplace_back(*it);
                    nodeList.erase(it);
                }
            } break;
            
            default: break;
        }
    }

    list<CSTNode*>::reverse_iterator lastSemicolon;
    bool hasSemicolon = false;
    for (list<CSTNode*>::reverse_iterator nodeit = nodeList.rbegin(); nodeit != nodeList.rend();) {
        switch ((*nodeit)->token.id)
        {
            case TOK_SEMICOLON:
                lastSemicolon = nodeit;
                hasSemicolon = true;
                nodeit++;
                break;
            
            case TOK_THEN:
            case TOK_DO:
                (*nodeit)->RHSChildren.emplace_front(*lastSemicolon);
                nodeList.erase(prev(lastSemicolon.base()));
                nodeit++;
                switch ((*nodeit)->token.id) {
                    case TOK_WHEN:
                    case TOK_IF:
                    case TOK_WHILE:
                    case TOK_REPEAT:
                        (*nodeit)->RHSChildren.emplace_front(*prev(nodeit));
                        break;

                    default:
                        throw UnexpectedTokenException((*nodeit)->token);
                }
                break;

            /*case TOK_WHEN:
            case TOK_IF:
            case TOK_WHILE:
            case TOK_REPEAT:
                hasSemicolon = false;
                nodeit++;
                break;
            */
            default:
                if (hasSemicolon) {
                    (*lastSemicolon)->LHSChildren.emplace_front(*nodeit);
                    list<CSTNode*>::iterator erased = prev(nodeit.base());
                    nodeList.erase(erased);
                } else nodeit++;
                break;
        }
    }
}

/*void CST::parseFlowControl(list<CSTNode*>& nodeList)
{
    for (CSTNode* nodeptr : nodeList) {
        if (!nodeptr->LHSChildren.empty()) parseFlowControl(nodeptr->LHSChildren);
        if (!nodeptr->RHSChildren.empty()) parseFlowControl(nodeptr->RHSChildren);
    }

    TokenID singleStatementKeyword;
    for (list<CSTNode*>::iterator fc = nodeList.begin(); fc != nodeList.end(); fc++)
    {
        singleStatementKeyword = TOK_DO;
        switch ((*fc)->token.id)
        {
            case TOK_WHEN:
                for (list<CSTNode*>::iterator it = next(fc);;) {
                    if ((*it)->token.id == TOK_OPENCURLYBR) {
                        (*fc)->RHSChildren.emplace_back(*it);
                        nodeList.erase(it);
                        break;
                    } else {
                        (*fc)->LHSChildren.emplace_back(*it);
                        list<CSTNode*>::iterator erased = it;
                        it++;
                        nodeList.erase(erased);
                    }
                }
                break;
            
            case TOK_IF:
                singleStatementKeyword = TOK_THEN;
            case TOK_WHILE:
            case TOK_REPEAT:
                for (list<CSTNode*>::iterator it = next(fc);;) {
                    if ((*it)->token.id == TOK_OPENCURLYBR) {
                        (*fc)->RHSChildren.emplace_back(*it);
                        nodeList.erase(it);
                        break;
                    } else if ((*it)->token.id == singleStatementKeyword) {
                        list<CSTNode*>::iterator erased;
                        for (list<CSTNode*>::iterator jt = next(it);;) {
                            (*it)->RHSChildren.emplace_back(*jt);
                            if ((*jt)->token.id == TOK_SEMICOLON) {
                                nodeList.erase(jt);
                                break;
                            } else {
                                erased = jt;
                                jt++;
                                nodeList.erase(erased);
                            }
                        }
                        (*fc)->RHSChildren.emplace_back(*it);
                        erased = it;
                        it++;
                        nodeList.erase(erased);
                        break;
                    } else {
                        (*fc)->LHSChildren.emplace_back(*it);
                        list<CSTNode*>::iterator erased = it;
                        it++;
                        nodeList.erase(erased);
                    }
                }
                break;
            
            case TOK_ELSE:
            {
                list<CSTNode*>::iterator it = next(fc);
                if ((*it)->token.id == TOK_OPENCURLYBR) {
                    (*fc)->RHSChildren.emplace_back(*it);
                    nodeList.erase(it);
                } else {
                    list<CSTNode*>::iterator erased;
                    for (;;) {
                        (*fc)->RHSChildren.emplace_back(*it);
                        if ((*it)->token.id == TOK_SEMICOLON) {
                            nodeList.erase(it);
                            break;
                        } else {
                            erased = it;
                            it++;
                            nodeList.erase(erased);
                        }
                    }
                }

                it = prev(fc);
                if ((*it)->token.id == TOK_IF) {
                    (*it)->RHSChildren.emplace_back(*fc);
                    nodeList.erase(fc);
                    fc = it;
                }
            } break;

            default: break;
        }
    }
}

void CST::parseSemicolons(list<CSTNode*>& nodeList)
{
    for (CSTNode* nodeptr : nodeList) {
        if (!nodeptr->LHSChildren.empty()) parseSemicolons(nodeptr->LHSChildren);
        if (!nodeptr->RHSChildren.empty()) parseSemicolons(nodeptr->RHSChildren);
    }
    
    list<CSTNode*>::reverse_iterator lastSemicolon;
    bool hasSemicolon = false;
    for (list<CSTNode*>::reverse_iterator nodeit = nodeList.rbegin(); nodeit != nodeList.rend();) {
        switch ((*nodeit)->token.id)
        {
            case TOK_SEMICOLON:
                lastSemicolon = nodeit;
                hasSemicolon = true;
                nodeit++;
                break;
            
            case TOK_WHEN:
            case TOK_IF:
            case TOK_WHILE:
            case TOK_REPEAT:
                hasSemicolon = false;
                nodeit++;
                break;
            
            default:
                if (hasSemicolon) {
                    (*lastSemicolon)->LHSChildren.emplace_front(*nodeit);
                    list<CSTNode*>::iterator erased = prev(nodeit.base());
                    nodeList.erase(erased);
                } else nodeit++;
                break;
        }
    }
}*/

//Idea: function parseCommas:
//  if commas present in children:
//      if $ present, assign all items after $ to first comma and assign comma to $
//      else, assign all items to first comma (items LHS, commas RHS)

void CST::parseTypes(list<CSTNode*>& nodeList)
{
    for (CSTNode* nodeptr : nodeList) {
        if (!nodeptr->LHSChildren.empty()) parseTypes(nodeptr->LHSChildren);
        if (!nodeptr->RHSChildren.empty()) parseTypes(nodeptr->RHSChildren);
    }

    for (list<CSTNode*>::reverse_iterator nodeit = nodeList.rbegin(); nodeit != nodeList.rend();) {
        if ((*nodeit)->token.id == TOK_IDENTIFIER) {
            list<CSTNode*>::reverse_iterator type = next(nodeit);
            if (type != nodeList.rend() && (*type)->token.id == TOK_IDENTIFIER) {
                (*nodeit)->LHSChildren.emplace_front(*type);
                nodeList.erase(prev(type.base()));
            } else nodeit++;
        } else nodeit++;
    }
}

// Idea: make "if", "repeat" etc. operators, and make "then"/"do" be parsed in parseSemicolons:
// When parseSemicolons encounters "then"/"do" while iterating backwards, it assigns the current semicolon to "then"
// So "if" etc. can always have valency {0, 2} and have lower precedence than the operators making up a condition
void CST::parseOperators(list<CSTNode*>& nodeList)
{
    for (CSTNode* nodeptr : nodeList) {
        if (!nodeptr->LHSChildren.empty()) parseOperators(nodeptr->LHSChildren);
        if (!nodeptr->RHSChildren.empty()) parseOperators(nodeptr->RHSChildren);
    }

    list<list<CSTNode*>::iterator> sorted;
    for (list<CSTNode*>::iterator it = nodeList.begin(); it != nodeList.end(); it++)
        sorted.emplace_back(it);
    sorted.sort(comparePrecedence);

    for (list<list<CSTNode*>::iterator>::iterator op = sorted.begin(); op != sorted.end(); op++)
    {
        list<CSTNode*>::iterator LHSLimit = *op;
        for (unsigned i = 0; i < (**op)->lhs; i++) {
            if (LHSLimit == nodeList.begin()) {
                (**op)->lhs = i;
                break;
            } else LHSLimit--;
        }

        list<CSTNode*>::iterator RHSLimit = *op;
        for (unsigned i = 0; i < ((**op)->rhs)+1; i++) {
            RHSLimit++;
            if (RHSLimit == nodeList.end()) {
                (**op)->rhs = i;
                break;
            }
        }

        list<CSTNode*>* childList = &((**op)->LHSChildren);
        for (list<CSTNode*>::iterator it = LHSLimit; it != RHSLimit;) {
            if (it != *op) {
                childList->emplace_back(*it);
                list<CSTNode*>::iterator nlerased = it;
                list<list<CSTNode*>::iterator>::iterator serased = find(sorted.begin(), sorted.end(), it);
                it++;
                nodeList.erase(nlerased);
                sorted.erase(serased);
            } else {
                childList = &((**op)->RHSChildren);
                it++;
            }
        }
    }
}

bool CST::comparePrecedence(const list<CSTNode*>::iterator it1, const list<CSTNode*>::iterator it2)
{
    return (*it1)->precedence > (*it2)->precedence;
}