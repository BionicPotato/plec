#include <cstdio>
#include "../exceptions.hpp"

AmbiguousStatementException::AmbiguousStatementException(std::shared_ptr<std::stack<std::shared_ptr<Expression>>> exprs): exprs(exprs) {}

const char* AmbiguousStatementException::what() const noexcept
{
    int cx = snprintf(errorMessage, sizeof(errorMessage), "%s:%u:%u Ambiguous parse between ", exprs->top()->token.filename, exprs->top()->token.lineNo, exprs->top()->token.colNo);
    while (exprs->size() > 0) {
        if (cx >= 0 && cx < sizeof(errorMessage)) {
            cx = snprintf(errorMessage+cx, sizeof(errorMessage)-cx, (exprs->size() > 2 ? "'%s', " : (exprs->size() == 2 ? "'%s' and " : "'%s'")), typeid(exprs->top()).name());
            exprs->pop();
        }
    }
    return errorMessage;
}
