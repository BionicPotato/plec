#include "programstmt.hpp"
#include "../visitors/astvisitor.hpp"
#include "../runner.hpp"
#include "targettype.hpp"

using namespace std;

ProgramStmt::ProgramStmt(Token& token, string programName)
: Statement(token), programName(programName) {}

void ProgramStmt::run(Runner& r)
{
    r.setTarget(token.filename, TARG_PROGRAM, programName);
}

void ProgramStmt::accept(ASTVisitor& visitor)
{
    visitor.doProgramStmt(*this);
}

