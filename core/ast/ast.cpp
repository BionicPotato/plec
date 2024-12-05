#include "ast.hpp"
#include "../visitors/astvisitor.hpp"
#include "statement.hpp"
#include <memory>

using namespace std;

AST::AST(vector<const char*> args)
: configureRunner(ASTConfigureRunner(*this))
{
    for (const char* filename : args) {
        files.push_back(make_unique<File>(filename));
    }
}

void AST::accept(ASTVisitor& visitor) const
{
    visitor.doAST(*this);
}

void AST::parse()
{
    unique_ptr<const Statement> stp;
    for (unique_ptr<File>& filep : files)
    {
        FileStmtStream filess(make_shared<Lexer>(filep->filename));
        while (filess.getNextStatement(stp))
            filep->statements.push_back(std::move(stp));
    }
}

void AST::configure()
{
    for (unique_ptr<File>& filep : files)
    {
        for (unique_ptr<const Statement>& stp : filep->statements) {
            stp->run(configureRunner);
        }
    }
}

