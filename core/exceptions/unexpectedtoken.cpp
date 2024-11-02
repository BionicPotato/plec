#include <cstdio>
#include "../exceptions.hpp"

UnexpectedTokenException::UnexpectedTokenException(Token tok): token(tok) {}

const char* UnexpectedTokenException::what() const noexcept
{
    snprintf(errorMessage, sizeof(errorMessage), "%s:%u:%u Unexpected token '%s'", token.filename, token.lineNo, token.colNo, token.content.c_str());
    return errorMessage;
}

