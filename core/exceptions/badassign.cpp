#include <cstdio>
#include "../exceptions.hpp"

using namespace std;

BadAssignException::BadAssignException(const string givenType, shared_ptr<Expression> expr, const string expectedType): givenType(givenType), expr(expr), expectedType(expectedType) {}

const char* BadAssignException::what() const noexcept
{
    snprintf(errorMessage, sizeof(errorMessage), "%s:%u:%u Cannot assign a value to %s '%s'; expected %s", expr->token.filename, expr->token.lineNo, expr->token.colNo, givenType.c_str(), expr->token.content.c_str(), expectedType.c_str());
    return errorMessage;
}

