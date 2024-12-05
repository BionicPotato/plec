#include "programstmt.hpp"
#include "../visitors/astvisitor.hpp"
#include "../runner.hpp"
#include "targettype.hpp"

using namespace std;

ProgramStmt::ProgramStmt(Token& token, string programName)
: Statement(token), programName(programName) {}

void ProgramStmt::run(Runner& r) const
{
    r.setTarget(token.filename, TARG_PROGRAM, programName);
}

void ProgramStmt::accept(ASTVisitor& visitor) const
{
    visitor.doProgramStmt(*this);
}

