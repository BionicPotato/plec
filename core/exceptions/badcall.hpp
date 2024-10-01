#pragma once

#include <exception>
#include <memory>
#include <string>

class Expression;

class BadCallException: public std::exception
{
    public:
        BadCallException(const std::string givenType, std::shared_ptr<Expression> expr);
        virtual const char* what() const noexcept;

    private:
        const std::string givenType;
        std::shared_ptr<Expression> expr;
};