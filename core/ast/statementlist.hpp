#pragma once

#include "astvisitable.hpp"
#include <memory>
#include <vector>

struct Token;
class Statement;

class StatementList: public ASTVisitable
{
    public:
        std::vector<std::shared_ptr<Statement>> statements;

        virtual void accept(ASTVisitor& visitor);
};
