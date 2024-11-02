#include "astconfigure.hpp"
#include "../ast/ast.hpp"
#include "../ast/program.hpp"

using namespace std;

ASTConfigureRunner::ASTConfigureRunner(AST& ast, shared_ptr<File> filep): filep(filep), ast(ast) {}

void ASTConfigureRunner::addToTarget(shared_ptr<Statement> stp)
{
    targetp->statements.push_back(stp);
}

void ASTConfigureRunner::setTarget(TargetType targetType, string targetName)
{
    for (shared_ptr<Target> tp : ast.targets)
    {
        if (tp->name == targetName) {
            targetp = tp;
            targetp->files.push_back(filep);
            return;
        }
    }

    switch (targetType)
    {
        case TARG_PROGRAM:
            targetp = make_shared<Program>(targetName);
            ast.targets.push_back(targetp);
        break;
        
        case TARG_LIB:
            //targetp = make_shared...
        break;
    }
}

