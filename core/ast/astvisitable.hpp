#pragma once

class ASTVisitor;

class ASTVisitable
{
    public:
        virtual ~ASTVisitable() = default;
        virtual void accept(ASTVisitor& visitor) const = 0;
};

