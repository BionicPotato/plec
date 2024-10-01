#pragma once

#include <string>

enum TokenID {
    TOK_UNKNOWN = 0,

    //Misc
    TOK_COMMENT = 0x01,
    TOK_STRING,
    TOK_COLON,
    TOK_CALL,

    //Grouping
    TOK_OPENPAREN = 0x10,
    TOK_CLOSEPAREN,
    TOK_OPENSQBR,
    TOK_CLOSESQBR,
    TOK_OPENCURLYBR,
    TOK_CLOSECURLYBR,

    //Separating
    TOK_COMMA = 0x20,
    TOK_SEMICOLON,

    //Arithmetic operators
    TOK_PLUS = 0x30,
    TOK_MINUS,
    TOK_ASTERISK,
    TOK_SLASH,
    TOK_MOD,
    TOK_CARET,

    //Comparison
    TOK_EQUAL = 0x40,
    TOK_NOT_EQUAL,
    TOK_GREATER_THAN,
    TOK_LESS_THAN,
    TOK_GREATER_OR_EQUAL,
    TOK_LESS_OR_EQUAL,
    
    //Logical operators
    TOK_NOT = 0x50,
    TOK_AND,
    TOK_OR,
    TOK_XOR,

    //Alphanumeric
    TOK_NUMBER = 0x80,
    TOK_IDENTIFIER,
    TOK_PROGRAM,
    TOK_IMPORT,
    TOK_WHEN,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_WHILE,
    TOK_REPEAT,
    TOK_DO,
    TOK_RETURN,
    TOK_THROW,
    TOK_EXIT,

    TOK_EOF = 0xff
};

std::string getTokenIDString(TokenID id);