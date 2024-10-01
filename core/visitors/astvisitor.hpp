#pragma once

class AST;
class StatementList;
class Statement;
class ProgramStmt;
class Expression;
class AddExpr;
class BlockExpr;
class VariableAssignExpr;
class FunctionCallExpr;

class ASTVisitor
{
    public:
        virtual void doAST(AST& ast) = 0;
        virtual void doStatementList(StatementList& stmtlist) = 0;
        virtual void doStatement(Statement& stmt) = 0;
	virtual void doProgramStmt(ProgramStmt& stmt) = 0;
        virtual void doExpression(Expression& expr) = 0;
        virtual void doAddExpr(AddExpr& ae) = 0;
        virtual void doBlockExpr(BlockExpr& be) = 0;
        virtual void doVariableAssignExpr(VariableAssignExpr& vae) = 0;
        virtual void doFunctionCallExpr(FunctionCallExpr& fce) = 0;
};
