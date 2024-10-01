#pragma once

#include <exception>
#include "../token.hpp"

class UnknownTokenException: public std::exception
{
    public:
        UnknownTokenException(Token tok);
        virtual const char* what() const noexcept;

    private:
        Token token;
};