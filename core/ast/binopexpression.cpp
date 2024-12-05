#include "binopexpression.hpp"

BinOpExpression::BinOpExpression(Token& token, std::unique_ptr <const Expression> lhs, std::unique_ptr<const Expression> rhs)
: Expression(token), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

