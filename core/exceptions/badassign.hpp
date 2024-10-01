#pragma once

#include <exception>
#include <memory>
#include <string>

class Expression;

class BadAssignException: public std::exception
{
    public:
        BadAssignException(const std::string givenType, std::shared_ptr<Expression> expr, const std::string expectedType);
        virtual const char* what() const noexcept;

    private:
        const std::string givenType;
        std::shared_ptr<Expression> expr;
        const std::string expectedType;
};