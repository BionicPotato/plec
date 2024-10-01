#pragma once

#include "astvisitable.hpp"
#include "target.hpp"
#include "file.hpp"
#include "../lexer.hpp"
#include "../runners/astrunner.hpp"
#include <memory>
#include <vector>

class AST: public ASTVisitable
{
    public:
        std::vector<std::shared_ptr<File>> files;
        std::vector<std::shared_ptr<Target>> targets;
        ASTRunner runner;

        AST(std::vector<const char*> args);
        virtual void accept(ASTVisitor& visitor);
        void parse();
        void prerun();
};
