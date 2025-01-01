#include "../../ast/expressions.hpp"
#include "../../ast/ast.hpp"
#include "../../ast/statement.hpp"
#include "../../ast/programstmt.hpp"
#include "print.hpp"
#include <iostream>
#include <memory>

using namespace std;

ASTPrintVisitor::ASTPrintVisitor() {}

ASTPrintVisitor& ASTPrintVisitor::instance()
{
    static ASTPrintVisitor visitor{};
    return visitor;
}

void ASTPrintVisitor::printBinOp(const BinOpExpression& boe)
{
    indent++;
    cout << string(indent, '\t')
         << "LHS:"
         << endl;
    indent++;
    boe.lhs->accept(*this);
    indent--;
    cout << string(indent, '\t')
         << "RHS:"
         << endl;
    indent++;
    boe.rhs->accept(*this);
    indent -= 2;
}

void ASTPrintVisitor::doAddExpr(const AddExpr& ae)
{
    cout << string(indent, '\t')
         << "Addition: '"
         << endl;
    printBinOp(ae);
}

void ASTPrintVisitor::doArrayExpr(const ArrayExpr& ae)
{
    cout << string(indent, '\t')
         << "Array: "
         << endl;
    indent++;
    for (const unique_ptr<const Expression>& expr : ae.expressions)
        expr->accept(*this);
    indent--;
}

void ASTPrintVisitor::doAST(const AST& ast)
{
    for (const unique_ptr<File>& file : ast.files) {
        cout << string(indent, '\t')
            << "File: "
            << file->filename
            << endl;
        indent++;
        file->accept(*this);
        indent--;
    }
    for (const unique_ptr<Target>& target : ast.targets) {
        cout << string(indent, '\t')
             << "Target: "
             << targetTypeNames[target->type]
             << ' '
             << target->name
             << endl;
        indent++;
        target->accept(*this);
        indent--;
    }
}

void ASTPrintVisitor::doBlockExpr(const BlockExpr& be)
{
    cout << string(indent, '\t')
         << "Block:"
         << endl;
    ++indent;
    be.dataBlock->accept(*this);
    be.statementBlock->accept(*this);
}

void ASTPrintVisitor::doCurlyBrExpr(const CurlyBrExpr& cbe)
{
    cout << string(indent, '\t')
         << "Statements:"
         << endl;
    indent++;
    for (const unique_ptr<const Statement>& stp : cbe.statements)
        stp->accept(*this);
    indent--;
}

void ASTPrintVisitor::doDeclExpr(const DeclExpr& de)
{
    cout << string(indent, '\t')
         << "Variable declaration:"
         << endl;
    indent++;
    cout << string(indent, '\t')
         << "Type:"
         << endl;
    indent++;
    de.lhs->accept(*this);
    indent--;
    cout << string(indent, '\t')
         << "Variable:"
         << endl;
    indent++;
    de.rhs->accept(*this);
    indent -= 2;
}

void ASTPrintVisitor::doExpression(const Expression& expr)
{
    // also: print expression's datatype
    cout << string(indent, '\t')
         << "Expression: "
         << typeid(expr).name()
         << " '"
         << expr.token.content
         << '\''
         << endl;
}

void ASTPrintVisitor::doFunctionCallExpr(const FunctionCallExpr& fce)
{
    cout << string(indent, '\t')
         << "Function call: '"
         << fce.callee->token.content;
    size_t argssize = fce.args.size();
    if (argssize == 0) {
        cout << "' with no arguments" << endl;
        return;
    }
    else if (argssize == 1) cout << "' with 1 argument";
    else cout << "' with "
              << argssize
              << " arguments";
    cout << endl;
    indent++;
    for (const unique_ptr<const Expression>& arg : fce.args)
        arg->accept(*this);
    indent--;
}

void ASTPrintVisitor::doProgramStmt(const ProgramStmt& stmt)
{
    cout << string(indent, '\t')
         << "Program statement: "
         << stmt.programName
         << endl;
}

void ASTPrintVisitor::doStatement(const Statement& stmt)
{
    cout << string(indent, '\t')
         << "Statement: "
         << typeid(stmt).name()
         << endl;
}

void ASTPrintVisitor::doStatementList(const StatementList& stmtlist)
{
    for (const unique_ptr<const Statement>& stmt : stmtlist.statements) {
        stmt->accept(*this);
    }
}

void ASTPrintVisitor::doTarget(const Target& t)
{
    for (const File* file : t.files) {
        cout << string(indent, '\t')
             << file->filename
             << endl;
    }
}

void ASTPrintVisitor::doVariableAssignExpr(const VariableAssignExpr& vae)
{
    cout << string(indent, '\t')
         << "Variable assignment:"
         << endl;
    printBinOp(vae);
}

