#include "tokenid.hpp"

using namespace std;

string getTokenIDString(TokenID id)
{
    switch (id)
    {
        case TOK_UNKNOWN: return "UNKNOWN";

    //Misc
        case TOK_COMMENT: return "COMMENT";
        case TOK_STRING: return "STRING";
        case TOK_COLON: return "COLON";
        case TOK_CALL: return "CALL";

    //Grouping
        case TOK_OPENPAREN: return "OPENPAREN";
        case TOK_CLOSEPAREN: return "CLOSEPAREN";
        case TOK_OPENSQBR: return "OPENSQBR";
        case TOK_CLOSESQBR: return "CLOSESQBR";
        case TOK_OPENCURLYBR: return "OPENCURLYBR";
        case TOK_CLOSECURLYBR: return "CLOSECURLYBR";

    //Separating
        case TOK_COMMA: return "COMMA";
        case TOK_SEMICOLON: return "SEMICOLON";

    //Arithmetic operators
        case TOK_PLUS: return "PLUS";
        case TOK_MINUS: return "MINUS";
        case TOK_ASTERISK: return "ASTERISK";
        case TOK_SLASH: return "SLASH";
        case TOK_MOD: return "MOD";
        case TOK_CARET: return "CARET";

    //Comparison
        case TOK_EQUAL: return "EQUAL";
        case TOK_NOT_EQUAL: return "NOT_EQUAL";
        case TOK_GREATER_THAN: return "GREATER_THAN";
        case TOK_LESS_THAN: return "LESS_THAN";
        case TOK_GREATER_OR_EQUAL: return "GREATER_OR_EQUAL";
        case TOK_LESS_OR_EQUAL: return "LESS_OR_EQUAL";
    
    //Logical operators
        case TOK_NOT: return "NOT";
        case TOK_AND: return "AND";
        case TOK_OR: return "OR";
        case TOK_XOR: return "XOR";

    //Alphanumeric
        case TOK_NUMBER: return "NUMBER";
        case TOK_IDENTIFIER: return "IDENTIFIER";
        case TOK_PROGRAM: return "PROGRAM";
        case TOK_IMPORT: return "IMPORT";
        case TOK_WHEN: return "WHEN";
        case TOK_IF: return "IF";
        case TOK_THEN: return "THEN";
        case TOK_ELSE: return "ELSE";
        case TOK_WHILE: return "WHILE";
        case TOK_REPEAT: return "REPEAT";
        case TOK_DO: return "DO";
        case TOK_RETURN: return "RETURN";
        case TOK_THROW: return "THROW";
        case TOK_EXIT: return "EXIT";

        case TOK_EOF: return "EOF";
    }
    return "UNKNOWN";
}