#include "lexer.hpp"
#include "tokenid.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>

using namespace std;

/* struct noop
{
    void operator()(...) const {}
}; */

void deleteIstreamNoop(istream* p) {}
void deleteIstream(istream* p)
{
    delete p;
}

bool isalnumund(char c) {return isalnum(c) || c == '_';}
bool isalund(char c) {return isalpha(c) || c == '_';}

using IstreamDeleter = void (*)(istream*);
unique_ptr<istream, IstreamDeleter> getInput(const char* filename)
{
    unique_ptr<istream, IstreamDeleter> in(&cin, deleteIstreamNoop);
    if (filename[0] != '\0')
        in = unique_ptr<ifstream, IstreamDeleter>(new ifstream(filename), deleteIstream);
    return in;
}

Lexer::Lexer(const char* file_name):
    filename((file_name[0] == '\0') ? "stdin" : file_name),
    input(getInput(file_name)),
    lineNo(1),
    colNo(0)
    {}

bool Lexer::getNextChar()
{
    if (!input->get(readChar)) return false;
    if (readChar == '\n') {
        lineNo++;
        oldColNos.push(colNo);
        colNo = 0;
    } else colNo++;
    return true;
}

void Lexer::ungetChar()
{
    if (readChar == '\n') {
        lineNo--;
        colNo = oldColNos.top();
        oldColNos.pop();
    }
    else colNo--;
    input->unget();
}

bool Lexer::getNextToken(Token& tok)
{
    do {
        if (!getNextChar()) return false;
        if (readChar == '/')
        {
            if (!getNextChar()) return false;
            if (readChar == '/') {
                do {
                    if (!getNextChar()) return false;
                } while (readChar != '\n');
            } else if (readChar == '*') {
                for (;;) {
                    if (!getNextChar()) return false;
                    if (readChar == '*') {
                        if (!getNextChar()) return false;
                        if (readChar == '/') {
                            if (!getNextChar()) return false;
                            break;
                        }
                    }
                }
            } else {
                ungetChar();
            }
        }
    }
    while (isspace(readChar));
    
    readString = readChar;
    tok.lineNo = lineNo;
    tok.colNo = colNo;

    if (readChar == '"')
    {
        for (getNextChar(); readChar != '"'; getNextChar()) {
            readString += readChar;
        }
        readString += readChar; // last '"'
    }
    else if (isalnumund(readChar))
    {
        for (getNextChar(); isalnumund(readChar); getNextChar()) {
            readString += readChar;
        }
        ungetChar();
    }

    tok.id = getTokenID(readString);
    tok.content = readString;
    tok.filename = filename;

    readString.clear();

    return true;
}

TokenID Lexer::getTokenID(const string& tokstr)
{
    static map<string, TokenID> multiCharTokens =
    {
        {"!=", TOK_NOT_EQUAL},
        {">=", TOK_GREATER_OR_EQUAL},
        {"<=", TOK_LESS_OR_EQUAL},

        {"program", TOK_PROGRAM},
        {"import", TOK_IMPORT},
        {"when", TOK_WHEN},
        {"if", TOK_IF},
        {"then", TOK_THEN},
        {"else", TOK_ELSE},
        {"while", TOK_WHILE},
        {"repeat", TOK_REPEAT},
        {"do", TOK_DO},
        {"return", TOK_RETURN},
        {"throw", TOK_THROW},
        {"exit", TOK_EXIT},
    };

    if (tokstr[0] == '"') return TOK_STRING;
    else if (isdigit(tokstr[0])) return TOK_NUMBER;
    else if (tokstr.length() > 1)
    {
        map<string, TokenID>::iterator it = multiCharTokens.find(tokstr);
        if (it != multiCharTokens.end()) return it->second;
        else if (isalund(tokstr[0])) return TOK_IDENTIFIER;
        else return TOK_UNKNOWN;
    }
    else if (isalund(tokstr[0])) return TOK_IDENTIFIER;
    else switch (tokstr[0])
    {
        case ':': return TOK_COLON;
        case '$': return TOK_CALL;
        case '(': return TOK_OPENPAREN;
        case ')': return TOK_CLOSEPAREN;
        case '[': return TOK_OPENSQBR;
        case ']': return TOK_CLOSESQBR;
        case '{': return TOK_OPENCURLYBR;
        case '}': return TOK_CLOSECURLYBR;
        case ',': return TOK_COMMA;
        case ';': return TOK_SEMICOLON;
        case '+': return TOK_PLUS;
        case '-': return TOK_MINUS;
        case '*': return TOK_ASTERISK;
        case '/': return TOK_SLASH;
        case '%': return TOK_MOD;
        case '^': return TOK_CARET;
        case '=': return TOK_EQUAL;
        case '>': return TOK_GREATER_THAN;
        case '<': return TOK_LESS_THAN;
        case '!': return TOK_NOT;
        case '&': return TOK_AND;
        case '|': return TOK_OR;
        case '`': return TOK_XOR;
        default: return TOK_UNKNOWN;
    }

    return TOK_UNKNOWN;
}

