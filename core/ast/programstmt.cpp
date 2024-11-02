#include "programstmt.hpp"
#include "../visitors/astvisitor.hpp"
#include "../runner.hpp"
#include "targettype.hpp"

using namespace std;

ProgramStmt::ProgramStmt(string programName)
: programName(programName) {}

void ProgramStmt::run(Runner& r)
{
    r.setTarget(TARG_PROGRAM, programName);
}

void ProgramStmt::accept(ASTVisitor& visitor)
{
    visitor.doProgramStmt(*this);
}

