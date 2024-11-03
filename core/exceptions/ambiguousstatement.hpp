#pragma once

#include "../ast/expression.hpp"
#include <exception>
#include <memory>
#include <stack>

class AmbiguousStatementException: public std::exception
{
    public:
        AmbiguousStatementException(std::shared_ptr<std::stack<std::shared_ptr<Expression>>> exprs);
        virtual const char* what() const noexcept;

    private:
        std::shared_ptr<std::stack<std::shared_ptr<Expression>>> exprs;
};
