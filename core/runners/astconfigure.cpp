#include "astconfigure.hpp"
#include "../exceptions.hpp"
#include "../ast/ast.hpp"
#include "../ast/program.hpp"

using namespace std;

ASTConfigureRunner::ASTConfigureRunner(AST& ast): ast(ast) {}

void ASTConfigureRunner::setTarget(string filename, TargetType targetType, string targetName)
{
    File* filep;

    for (const unique_ptr<File>& fp : ast.files) {
        if (fp->filename == filename) {
            filep = fp.get();
            break;
        }
    }
    if (!filep) throw UnknownFilenameException(filename);

    for (const unique_ptr<Target>& tp : ast.targets)
    {
        if (tp->name == targetName) {
            if (tp->type != targetType) {
                //TODO: error: declaring a target with the same name but a different type!
            }
            tp->files.push_back(filep);
            return;
        }
    }

    unique_ptr<Target> tp;
    switch (targetType)
    {
        case TARG_PROGRAM:
            tp = make_unique<Program>(targetName);
            tp->files.push_back(filep);
            ast.targets.push_back(std::move(tp));
        break;
        
        case TARG_LIB:
            //tp = make_unique...
        break;
    }
}

