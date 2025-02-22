#pragma once

#include "../statementstream.hpp"

class Statement;

class FileStmtStream: public StatementStream
{
    public:
        using StatementStream::StatementStream;
    
    protected:
        virtual bool getNextToken(Token& tok);
        virtual bool checkCurlyBr(const Token& tok);
        virtual bool checkProgramStmt(Token& tok, std::unique_ptr<const Statement>& stp);
};
