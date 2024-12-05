#pragma once

#include "statement.hpp"
#include "../token.hpp"
#include <memory>

class ProgramStmt: public Statement
{
    public:
        std::string programName;

        ProgramStmt(Token& token, std::string programName);
	virtual void accept(ASTVisitor& visitor) const;
        virtual void run(Runner& r) const;
};

