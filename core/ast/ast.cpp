#include "ast.hpp"
#include "../visitors/astvisitor.hpp"
#include "statement.hpp"
#include <memory>

using namespace std;

AST::AST(vector<const char*> args)
: configureRunner(ASTConfigureRunner(*this, nullptr))
{
    for (const char* filename : args) {
        files.push_back(make_shared<File>(filename));
    }
}

void AST::accept(ASTVisitor& visitor)
{
    visitor.doAST(*this);
}

void AST::parse()
{
    shared_ptr<Statement> stp;
    for (shared_ptr<File> filep : files)
    {
        shared_ptr<Lexer> lexp = make_shared<Lexer>(filep->filename);
        FileStmtStream filess(lexp);
        while (filess.getNextStatement(stp))
            filep->statements.push_back(stp);
    }
}

void AST::configure()
{
    for (shared_ptr<File> filep : files)
    {
        for (shared_ptr<Statement> stp : filep->statements) {
            configureRunner.filep = filep;
            stp->run(configureRunner);
        }
    }
}
