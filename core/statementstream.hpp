#pragma once

#include "ast/expression.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include <memory>

class Statement;

class StatementStream
{
    public:
        const char* filename;

        StatementStream(std::shared_ptr<Lexer> lexp);
        bool getNextStatement(std::unique_ptr<const Statement>& stp);

    protected:
        std::unique_ptr<Expression> getExpression(const Token& start, TokenID end);
        virtual bool getNextToken(Token& tok) = 0;
        virtual bool checkCurlyBr(const Token& tok) = 0;
        virtual bool checkProgramStmt(Token& tok, std::unique_ptr<const Statement>& stp) = 0;
        std::shared_ptr<Lexer> lexp;
};
