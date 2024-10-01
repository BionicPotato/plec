#include <cstdio>
#include "../exceptions.hpp"

UnknownTokenException::UnknownTokenException(Token tok): token(tok) {}

const char* UnknownTokenException::what() const noexcept
{
    snprintf(errorMessage, sizeof(errorMessage), "%s:%u:%u Unknown token '%s'", token.filename, token.lineNo, token.colNo, token.content.c_str());
    return errorMessage;
}