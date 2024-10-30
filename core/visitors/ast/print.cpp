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

void ASTPrintVisitor::doAddExpr(AddExpr& ae)
{
    cout << string(indent, '\t')
         << "Addition: '"
         << ae.lhs->token.content
         << "' + '"
         << ae.rhs->token.content
         << '\''
         << endl;
}

void ASTPrintVisitor::doArrayExpr(ArrayExpr& ae)
{
    cout << string(indent, '\t')
         << "Array: "
         << endl;
    indent++;
    for (shared_ptr<Expression> expr : ae.expressions)
        expr->accept(*this);
    indent--;
}

void ASTPrintVisitor::doAST(AST& ast)
{
    for (shared_ptr<File> file : ast.files) {
        cout << string(indent, '\t')
            << "File: "
            << file->filename
            << endl;
        indent++;
        file->accept(*this);
        indent--;
    }
    for (shared_ptr<Target> target : ast.targets) {
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

void ASTPrintVisitor::doBlockExpr(BlockExpr& be)
{
    cout << string(indent, '\t')
         << "Block:"
         << endl;
    indent++;
    for (shared_ptr<Statement> stp : be.statements)
        stp->accept(*this);
    indent--;
}

void ASTPrintVisitor::doExpression(Expression& expr)
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

void ASTPrintVisitor::doFunctionCallExpr(FunctionCallExpr& fce)
{
    cout << string(indent, '\t')
         << "Function call: '"
         << fce.callee->token.content;
    size_t argssize = fce.args.size();
    if (argssize == 0) cout << "' with no arguments";
    else if (argssize == 1) cout << "' with 1 argument";
    else cout << "' with "
              << argssize
              << " arguments";
    cout << endl;
    indent++;
    for (shared_ptr<Expression> arg : fce.args)
        arg->accept(*this);
    indent--;
}

void ASTPrintVisitor::doProgramStmt(ProgramStmt& stmt)
{
    cout << string(indent, '\t')
         << "Program statement: "
         << stmt.programName
         << endl;
}

void ASTPrintVisitor::doStatement(Statement& stmt)
{
    cout << string(indent, '\t')
         << "Statement: "
         << typeid(stmt).name()
         << endl;
}

void ASTPrintVisitor::doStatementList(StatementList& stmtlist)
{
    for (shared_ptr<Statement> stmt : stmtlist.statements) {
        stmt->accept(*this);
    }
}

void ASTPrintVisitor::doVariableAssignExpr(VariableAssignExpr& vae)
{
    cout << string(indent, '\t')
         << "Variable assignment: '"
         << vae.variable->token.content
         << "' with value '"
         << vae.value->token.content
         << '\''
         << endl;
}

