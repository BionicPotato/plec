#pragma once

#include "astvisitable.hpp"
#include "target.hpp"
#include "file.hpp"
#include "../lexer.hpp"
#include "../runners/astconfigure.hpp"
#include <memory>
#include <vector>

class AST: public ASTVisitable
{
    public:
        const std::vector<const char*> filenames;
        std::vector<std::unique_ptr<File>> files;
        std::vector<std::unique_ptr<Target>> targets;
        ASTConfigureRunner configureRunner;

        AST(std::vector<const char*>&& args);
        virtual void accept(ASTVisitor& visitor) const;
        void parse();
        void configure();
};

