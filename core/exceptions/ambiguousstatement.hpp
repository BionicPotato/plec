#pragma once

#include "../ast/expression.hpp"
#include <exception>
#include <memory>
#include <stack>

class AmbiguousStatementException: public std::exception
{
    public:
        AmbiguousStatementException(std::unique_ptr<std::stack<std::unique_ptr<Expression>>> exprs);
        virtual const char* what() const noexcept;

    private:
        std::unique_ptr<std::stack<std::unique_ptr<Expression>>> exprs;
};
