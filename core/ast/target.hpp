#pragma once

#include "statementlist.hpp"
#include "targettype.hpp"
#include <string>

class File;

class Target: public ASTVisitable
{
    public:
        const std::string name;
        TargetType type;
        std::vector<const File*> files;

        Target(const std::string& name, TargetType type);
        virtual void accept(ASTVisitor& visitor) const;
};

