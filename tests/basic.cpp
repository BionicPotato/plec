#include "../core/tokenid.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if (getTokenIDString(TOK_UNKNOWN) != "UNKNOWN") return -1;
    if (getTokenIDString(TOK_COMMENT) != "COMMENT") return -1;
    if (getTokenIDString(TOK_STRING) != "STRING") return -1;
    if (getTokenIDString(TOK_COLON) != "COLON") return -1;
    if (getTokenIDString(TOK_CALL) != "CALL") return -1;
    if (getTokenIDString(TOK_OPENPAREN) != "OPENPAREN") return -1;
    if (getTokenIDString(TOK_CLOSEPAREN) != "CLOSEPAREN") return -1;
    if (getTokenIDString(TOK_OPENSQBR) != "OPENSQBR") return -1;
    if (getTokenIDString(TOK_CLOSESQBR) != "CLOSESQBR") return -1;
    if (getTokenIDString(TOK_OPENCURLYBR) != "OPENCURLYBR") return -1;
    if (getTokenIDString(TOK_CLOSECURLYBR) != "CLOSECURLYBR") return -1;
    if (getTokenIDString(TOK_COMMA) != "COMMA") return -1;
    if (getTokenIDString(TOK_SEMICOLON) != "SEMICOLON") return -1;
    if (getTokenIDString(TOK_PLUS) != "PLUS") return -1;
    if (getTokenIDString(TOK_MINUS) != "MINUS") return -1;
    if (getTokenIDString(TOK_ASTERISK) != "ASTERISK") return -1;
    if (getTokenIDString(TOK_SLASH) != "SLASH") return -1;
    if (getTokenIDString(TOK_MOD) != "MOD") return -1;
    if (getTokenIDString(TOK_CARET) != "CARET") return -1;
    if (getTokenIDString(TOK_EQUAL) != "EQUAL") return -1;
    if (getTokenIDString(TOK_NOT_EQUAL) != "NOT_EQUAL") return -1;
    if (getTokenIDString(TOK_GREATER_THAN) != "GREATER_THAN") return -1;
    if (getTokenIDString(TOK_LESS_THAN) != "LESS_THAN") return -1;
    if (getTokenIDString(TOK_GREATER_OR_EQUAL) != "GREATER_OR_EQUAL") return -1;
    if (getTokenIDString(TOK_LESS_OR_EQUAL) != "LESS_OR_EQUAL") return -1;
    if (getTokenIDString(TOK_NOT) != "NOT") return -1;
    if (getTokenIDString(TOK_AND) != "AND") return -1;
    if (getTokenIDString(TOK_OR) != "OR") return -1;
    if (getTokenIDString(TOK_XOR) != "XOR") return -1;
    if (getTokenIDString(TOK_NUMBER) != "NUMBER") return -1;
    if (getTokenIDString(TOK_IDENTIFIER) != "IDENTIFIER") return -1;
    if (getTokenIDString(TOK_PROGRAM) != "PROGRAM") return -1;
    if (getTokenIDString(TOK_IMPORT) != "IMPORT") return -1;
    if (getTokenIDString(TOK_WHEN) != "WHEN") return -1;
    if (getTokenIDString(TOK_IF) != "IF") return -1;
    if (getTokenIDString(TOK_THEN) != "THEN") return -1;
    if (getTokenIDString(TOK_ELSE) != "ELSE") return -1;
    if (getTokenIDString(TOK_WHILE) != "WHILE") return -1;
    if (getTokenIDString(TOK_REPEAT) != "REPEAT") return -1;
    if (getTokenIDString(TOK_DO) != "DO") return -1;
    if (getTokenIDString(TOK_RETURN) != "RETURN") return -1;
    if (getTokenIDString(TOK_THROW) != "THROW") return -1;
    if (getTokenIDString(TOK_EXIT) != "EXIT") return -1;
    if (getTokenIDString(TOK_EOF) != "EOF") return -1;
    return 0;
}

