#pragma once

#include "../astvisitor.hpp"
#include <cstdint>

class BinOpExpression;

class ASTPrintVisitor: public ASTVisitor
{
    public:
        static ASTPrintVisitor& instance();

        virtual void doAddExpr(AddExpr& ae);
        virtual void doArrayExpr(ArrayExpr& ae);
        virtual void doAST(AST& ast);
        virtual void doBlockExpr(BlockExpr& be);
        virtual void doDeclExpr(DeclExpr& de);
        virtual void doExpression(Expression& expr);
        virtual void doFunctionCallExpr(FunctionCallExpr& fce);
        virtual void doProgramStmt(ProgramStmt& stmt);
        virtual void doStatement(Statement& stmt);
        virtual void doStatementList(StatementList& stmtlist);
        virtual void doVariableAssignExpr(VariableAssignExpr& vae);
    
    private:
        uint8_t indent;

        ASTPrintVisitor();
        ASTPrintVisitor(const ASTPrintVisitor&);
        ASTPrintVisitor& operator= (const ASTPrintVisitor&);

        void printBinOp(BinOpExpression& boe);
};

