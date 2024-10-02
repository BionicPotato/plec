#pragma once

#include "../runner.hpp"
#include <memory>

class AST;
class Target;
class File;

class ASTConfigureRunner: public Runner
{
    public:
        std::shared_ptr<File> filep;
        
        ASTConfigureRunner(AST& ast, std::shared_ptr<File> filep);
        virtual void addToTarget(std::shared_ptr<Statement> stp);
        virtual void setTarget(TargetType targetType, std::string targetName);
    
    private:
        AST& ast;
        std::shared_ptr<Target> targetp;
};
