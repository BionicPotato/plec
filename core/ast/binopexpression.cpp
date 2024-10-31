#include "binopexpression.hpp"

BinOpExpression::BinOpExpression(Token& token, std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs)
: Expression(token), lhs(lhs), rhs(rhs) {}

