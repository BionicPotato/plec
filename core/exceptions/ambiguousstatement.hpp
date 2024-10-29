#pragma once

#include "../ast/expression.hpp"
#include <exception>
#include <memory>
#include <stack>

class AmbiguousStatementException: public std::exception
{
    public:
        AmbiguousStatementException(std::stack<std::shared_ptr<Expression>>& exprs);
        virtual const char* what() const noexcept;

    private:
        std::stack<std::shared_ptr<Expression>>& exprs;
};
