#pragma once

#include <exception>
#include "../token.hpp"

class UnexpectedTokenException: public std::exception
{
    public:
        UnexpectedTokenException(Token tok);
        virtual const char* what() const noexcept;

    private:
        Token token;
};