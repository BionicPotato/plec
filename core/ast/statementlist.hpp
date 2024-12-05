#pragma once

#include "astvisitable.hpp"
#include "statement.hpp"
#include <memory>
#include <vector>

struct Token;

class StatementList: public ASTVisitable
{
    public:
        std::vector<std::unique_ptr<const Statement>> statements;

        virtual void accept(ASTVisitor& visitor) const;
};

