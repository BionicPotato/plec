#include "operators.hpp"
#include "tokenid.hpp"
#include <utility>

using namespace std;

unsigned short getPrecedence(TokenID id)
{
    switch (id)
    {
        case TOK_NOT: return 300;
        case TOK_AND: return 290;
        case TOK_XOR: return 280;
        case TOK_OR: return 270;
        case TOK_EQUAL: return 200;
        case TOK_CARET: return 100;
        case TOK_ASTERISK: return 90;
        case TOK_SLASH: return 90;
        case TOK_MOD: return 90;
        case TOK_PLUS: return 80;
        case TOK_MINUS: return 80;
        case TOK_CALL: return 20;
        case TOK_COLON: return 10;
        case TOK_COMMA: return 5;
        case TOK_PROGRAM: return 2;
        case TOK_IMPORT: return 2;
        case TOK_RETURN: return 2;
        case TOK_THROW: return 2;
        case TOK_EXIT: return 2;
        default: return 0;
    }
}

bool isLeftAssociative(TokenID id)
{
    switch (id)
    {
        default: return true;
    }
}

pair<uint8_t, uint8_t> getValency(TokenID id)
{
    switch (id)
    {
        case TOK_NOT:
        case TOK_PROGRAM:
        case TOK_IMPORT:
        case TOK_RETURN:
        case TOK_THROW:
        case TOK_EXIT:
            return {0, 1};
        case TOK_AND:
        case TOK_XOR:
        case TOK_OR:
        case TOK_EQUAL:
        case TOK_CARET:
        case TOK_ASTERISK:
        case TOK_SLASH:
        case TOK_MOD:
        case TOK_PLUS:
        case TOK_MINUS:
        //case TOK_CALL:
        case TOK_COLON:
        //case TOK_COMMA:
            return {1, 1};
        default: return {0, 0};
    }
}