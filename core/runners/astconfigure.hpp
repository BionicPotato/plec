#pragma once

#include "../runner.hpp"
#include <memory>

class AST;
class Target;
class File;

class ASTConfigureRunner: public Runner
{
    public:
        ASTConfigureRunner(AST& ast);
        virtual void addToTarget(std::shared_ptr<Statement> stp);
        virtual void setTarget(std::string filename, TargetType targetType, std::string targetName);
    
    private:
        AST& ast;
        std::shared_ptr<Target> targetp;
};
