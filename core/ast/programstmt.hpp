#pragma once

#include "program.hpp"
#include "statement.hpp"
#include <memory>

class ProgramStmt: public Statement
{
    public:
        std::string programName;

        ProgramStmt(std::string programName);
	virtual void accept(ASTVisitor& visitor);
        virtual void run(Runner& r);
};
