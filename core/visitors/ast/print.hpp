#pragma once

#include "../astvisitor.hpp"
#include <cstdint>

class BinOpExpression;

class ASTPrintVisitor: public ASTVisitor
{
    public:
        static ASTPrintVisitor& instance();

        virtual void doAddExpr(const AddExpr& ae);
        virtual void doArrayExpr(const ArrayExpr& ae);
        virtual void doAST(const AST& ast);
        virtual void doBlockExpr(const BlockExpr& be);
        virtual void doCurlyBrExpr(const CurlyBrExpr& cbe);
        virtual void doDeclExpr(const DeclExpr& de);
        virtual void doExpression(const Expression& expr);
        virtual void doFunctionCallExpr(const FunctionCallExpr& fce);
        virtual void doProgramStmt(const ProgramStmt& stmt);
        virtual void doStatement(const Statement& stmt);
        virtual void doStatementList(const StatementList& stmtlist);
        virtual void doTarget(const Target& t);
        virtual void doVariableAssignExpr(const VariableAssignExpr& vae);
    
    private:
        uint8_t indent;

        ASTPrintVisitor();
        ASTPrintVisitor(const ASTPrintVisitor&);
        ASTPrintVisitor& operator= (const ASTPrintVisitor&);

        void printBinOp(const BinOpExpression& boe);
};

