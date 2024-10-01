#include <cstdio>
#include "../exceptions.hpp"

using namespace std;

BadCallException::BadCallException(const string givenType, shared_ptr<Expression> expr): givenType(givenType), expr(expr) {}

const char* BadCallException::what() const noexcept
{
    snprintf(errorMessage, sizeof(errorMessage), "%s:%u:%u Cannot call %s '%s'; must be a function", expr->token.filename, expr->token.lineNo, expr->token.colNo, givenType.c_str(), expr->token.content.c_str());
    return errorMessage;
}