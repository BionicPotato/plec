#pragma once

#include "statementlist.hpp"
#include "targettype.hpp"
#include <string>

class File;

class Target: public StatementList
{
    public:
        const std::string name;
        std::vector<std::shared_ptr<File>> files;
        TargetType type;

        Target(const std::string& name, TargetType type);
};