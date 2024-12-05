#pragma once

#include <memory>
#include <stack>
#include "token.hpp"

class Lexer
{
    public:
        const char* filename;

        Lexer(const char* filename);
        bool getNextToken(Token& tok);
    
    private:
        std::unique_ptr<std::istream, void (*)(std::istream*)> input;
        unsigned lineNo;
        unsigned colNo;
        std::stack<unsigned> oldColNos;
        char readChar;
        std::string readString;

        bool getNextChar();
        void ungetChar();
        TokenID getTokenID(const std::string& tokstr);
};

