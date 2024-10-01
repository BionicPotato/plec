#pragma once

#include "../astvisitor.hpp"
#include <cstdint>

class ASTPrintVisitor: public ASTVisitor
{
    public:
        static ASTPrintVisitor& instance();

        virtual void doAST(AST& ast);
        virtual void doStatementList(StatementList& stmtlist);
        virtual void doStatement(Statement& stmt);
        virtual void doProgramStmt(ProgramStmt& stmt);
        virtual void doAddExpr(AddExpr& ae);
        virtual void doBlockExpr(BlockExpr& be);
        virtual void doExpression(Expression& expr);
        virtual void doVariableAssignExpr(VariableAssignExpr& vae);
        virtual void doFunctionCallExpr(FunctionCallExpr& fce);
    
    private:
        uint8_t indent;

        ASTPrintVisitor();
        ASTPrintVisitor(const ASTPrintVisitor&);
        ASTPrintVisitor& operator= (const ASTPrintVisitor&);
};
