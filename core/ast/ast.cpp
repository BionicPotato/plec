#include "ast.hpp"
#include "../visitors/astvisitor.hpp"
#include "statement.hpp"
#include <memory>

using namespace std;

AST::AST(vector<const char*>&& args)
: filenames(std::move(args)), configureRunner(ASTConfigureRunner(*this)) {}

void AST::accept(ASTVisitor& visitor) const
{
    visitor.doAST(*this);
}

void AST::parse()
{
    unique_ptr<const Statement> stp;
    for (const char* filename : filenames)
    {
        vector<unique_ptr<const Statement>> stv;
        FileStmtStream filess(make_shared<Lexer>(filename));
        while (filess.getNextStatement(stp))
            stv.push_back(std::move(stp));
        files.push_back(make_unique<File>(std::move(stv), filename));
    }
}

void AST::configure()
{
    for (const unique_ptr<File>& filep : files)
    {
        for (const unique_ptr<const Statement>& stp : filep->statements) {
            stp->run(configureRunner);
        }
    }
}

