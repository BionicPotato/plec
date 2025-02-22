#pragma once

#include "expression.hpp"
#include <memory>

class BinOpExpression: public Expression
{
    public:
        const std::unique_ptr<const Expression> lhs;
        const std::unique_ptr<const Expression> rhs;

        BinOpExpression(Token& token, std::unique_ptr<const Expression> lhs, std::unique_ptr<const Expression> rhs);
};

