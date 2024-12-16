#pragma once

#include "astvisitable.hpp"
#include "statement.hpp"
#include <memory>
#include <vector>

struct Token;

class StatementList: public ASTVisitable
{
    public:
        const std::vector<std::unique_ptr<const Statement>> statements;

        StatementList(std::vector<std::unique_ptr<const Statement>>&& statements);
        virtual void accept(ASTVisitor& visitor) const;
};

