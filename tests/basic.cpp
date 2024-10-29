#include "test.hpp"
#include "../core/tokenid.hpp"

int main(int argc, char** argv)
{
    require(
        getTokenIDString(TOK_UNKNOWN) == "UNKNOWN",
        "TOK_UNKNOWN is not 'UNKNOWN'");
    require(
        getTokenIDString(TOK_COMMENT) == "COMMENT",
        "TOK_COMMENT is not 'COMMENT'");
    require(
        getTokenIDString(TOK_STRING) == "STRING",
        "TOK_STRING is not 'STRING'");
    require(
        getTokenIDString(TOK_COLON) == "COLON",
        "TOK_COLON is not 'COLON'");
    require(
        getTokenIDString(TOK_CALL) == "CALL",
        "TOK_CALL is not 'CALL'");
    require(
        getTokenIDString(TOK_OPENPAREN) == "OPENPAREN",
        "TOK_OPENPAREN is not 'OPENPAREN'");
    require(
        getTokenIDString(TOK_CLOSEPAREN) == "CLOSEPAREN",
        "TOK_CLOSEPAREN is not 'CLOSEPAREN'");
    require(
        getTokenIDString(TOK_OPENSQBR) == "OPENSQBR",
        "TOK_OPENSQBR is not 'OPENSQBR'");
    require(
        getTokenIDString(TOK_CLOSESQBR) == "CLOSESQBR",
        "TOK_CLOSESQBR is not 'CLOSESQBR'");
    require(
        getTokenIDString(TOK_OPENCURLYBR) == "OPENCURLYBR",
        "TOK_OPENCURLYBR is not 'OPENCURLYBR'");
    require(
        getTokenIDString(TOK_CLOSECURLYBR) == "CLOSECURLYBR",
        "TOK_CLOSECURLYBR is not 'CLOSECURLYBR'");
    require(
        getTokenIDString(TOK_COMMA) == "COMMA",
        "TOK_COMMA is not 'COMMA'");
    require(
        getTokenIDString(TOK_SEMICOLON) == "SEMICOLON",
        "TOK_SEMICOLON is not 'SEMICOLON'");
    require(
        getTokenIDString(TOK_PLUS) == "PLUS",
        "TOK_PLUS is not 'PLUS'");
    require(
        getTokenIDString(TOK_MINUS) == "MINUS",
        "TOK_MINUS is not 'MINUS'");
    require(
        getTokenIDString(TOK_ASTERISK) == "ASTERISK",
        "TOK_ASTERISK is not 'ASTERISK'");
    require(
        getTokenIDString(TOK_SLASH) == "SLASH",
        "TOK_SLASH is not 'SLASH'");
    require(
        getTokenIDString(TOK_MOD) == "MOD",
        "TOK_MOD is not 'MOD'");
    require(
        getTokenIDString(TOK_CARET) == "CARET",
        "TOK_CARET is not 'CARET'");
    require(
        getTokenIDString(TOK_EQUAL) == "EQUAL",
        "TOK_EQUAL is not 'EQUAL'");
    require(
        getTokenIDString(TOK_NOT_EQUAL) == "NOT_EQUAL",
        "TOK_NOT_EQUAL is not 'NOT_EQUAL'");
    require(
        getTokenIDString(TOK_GREATER_THAN) == "GREATER_THAN",
        "TOK_GREATER_THAN is not 'GREATER_THAN'");
    require(
        getTokenIDString(TOK_LESS_THAN) == "LESS_THAN",
        "TOK_LESS_THAN is not 'LESS_THAN'");
    require(
        getTokenIDString(TOK_GREATER_OR_EQUAL) == "GREATER_OR_EQUAL",
        "TOK_GREATER_OR_EQUAL is not 'GREATER_OR_EQUAL'");
    require(
        getTokenIDString(TOK_LESS_OR_EQUAL) == "LESS_OR_EQUAL",
        "TOK_LESS_OR_EQUAL is not 'LESS_OR_EQUAL'");
    require(
        getTokenIDString(TOK_NOT) == "NOT",
        "TOK_NOT is not 'NOT'");
    require(
        getTokenIDString(TOK_AND) == "AND",
        "TOK_AND is not 'AND'");
    require(
        getTokenIDString(TOK_OR) == "OR",
        "TOK_OR is not 'OR'");
    require(
        getTokenIDString(TOK_XOR) == "XOR",
        "TOK_XOR is not 'XOR'");
    require(
        getTokenIDString(TOK_NUMBER) == "NUMBER",
        "TOK_NUMBER is not 'NUMBER'");
    require(
        getTokenIDString(TOK_IDENTIFIER) == "IDENTIFIER",
        "TOK_IDENTIFIER is not 'IDENTIFIER'");
    require(
        getTokenIDString(TOK_PROGRAM) == "PROGRAM",
        "TOK_PROGRAM is not 'PROGRAM'");
    require(
        getTokenIDString(TOK_IMPORT) == "IMPORT",
        "TOK_IMPORT is not 'IMPORT'");
    require(
        getTokenIDString(TOK_WHEN) == "WHEN",
        "TOK_WHEN is not 'WHEN'");
    require(
        getTokenIDString(TOK_IF) == "IF",
        "TOK_IF is not 'IF'");
    require(
        getTokenIDString(TOK_THEN) == "THEN",
        "TOK_THEN is not 'THEN'");
    require(
        getTokenIDString(TOK_ELSE) == "ELSE",
        "TOK_ELSE is not 'ELSE'");
    require(
        getTokenIDString(TOK_WHILE) == "WHILE",
        "TOK_WHILE is not 'WHILE'");
    require(
        getTokenIDString(TOK_REPEAT) == "REPEAT",
        "TOK_REPEAT is not 'REPEAT'");
    require(
        getTokenIDString(TOK_DO) == "DO",
        "TOK_DO is not 'DO'");
    require(
        getTokenIDString(TOK_RETURN) == "RETURN",
        "TOK_RETURN is not 'RETURN'");
    require(
        getTokenIDString(TOK_THROW) == "THROW",
        "TOK_THROW is not 'THROW'");
    require(
        getTokenIDString(TOK_EXIT) == "EXIT",
        "TOK_EXIT is not 'EXIT'");
    require(
        getTokenIDString(TOK_EOF) == "EOF",
        "TOK_EOF is not 'EOF'");
    return 0;
}

