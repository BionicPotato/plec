#pragma once

class AddExpr;
class ArrayExpr;
class AST;
class BlockExpr;
class CurlyBrExpr;
class DeclExpr;
class Expression;
class FunctionCallExpr;
class ProgramStmt;
class Statement;
class StatementList;
class Target;
class VariableAssignExpr;

class ASTVisitor
{
    public:
        virtual void doAddExpr(const AddExpr& ae) = 0;
        virtual void doArrayExpr(const ArrayExpr& ae) = 0;
        virtual void doAST(const AST& ast) = 0;
        virtual void doBlockExpr(const BlockExpr& be) = 0;
        virtual void doCurlyBrExpr(const CurlyBrExpr& cbe) = 0;
        virtual void doDeclExpr(const DeclExpr& de) = 0;
        virtual void doExpression(const Expression& expr) = 0;
        virtual void doFunctionCallExpr(const FunctionCallExpr& fce) = 0;
	virtual void doProgramStmt(const ProgramStmt& stmt) = 0;
        virtual void doStatement(const Statement& stmt) = 0;
        virtual void doStatementList(const StatementList& stmtlist) = 0;
        virtual void doTarget(const Target& t) = 0;
        virtual void doVariableAssignExpr(const VariableAssignExpr& vae) = 0;
};

