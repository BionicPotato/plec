#pragma once

class ASTVisitor;

class ASTVisitable
{
    public:
        virtual void accept(ASTVisitor& visitor) = 0;
};