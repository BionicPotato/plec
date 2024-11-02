#pragma once

class AddExpr;
class ArrayExpr;
class AST;
class BlockExpr;
class DeclExpr;
class Expression;
class FunctionCallExpr;
class ProgramStmt;
class Statement;
class StatementList;
class VariableAssignExpr;

class ASTVisitor
{
    public:
        virtual void doAddExpr(AddExpr& ae) = 0;
        virtual void doArrayExpr(ArrayExpr& ae) = 0;
        virtual void doAST(AST& ast) = 0;
        virtual void doBlockExpr(BlockExpr& be) = 0;
        virtual void doDeclExpr(DeclExpr& de) = 0;
        virtual void doExpression(Expression& expr) = 0;
        virtual void doFunctionCallExpr(FunctionCallExpr& fce) = 0;
	virtual void doProgramStmt(ProgramStmt& stmt) = 0;
        virtual void doStatement(Statement& stmt) = 0;
        virtual void doStatementList(StatementList& stmtlist) = 0;
        virtual void doVariableAssignExpr(VariableAssignExpr& vae) = 0;
};

