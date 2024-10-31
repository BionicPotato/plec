#pragma once

#include "expression.hpp"
#include <memory>

class BinOpExpression: public Expression
{
    public:
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;

        BinOpExpression(Token& token, std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs);
};

