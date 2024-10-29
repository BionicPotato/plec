#include "test.hpp"
#include "../core/ast/expressions.hpp"
#include "../core/ast/statement.hpp"
#include "../core/ast/programstmt.hpp"
#include "../core/stmtstreams/file.hpp"
#include "../core/lexer.hpp"
#include <memory>

using namespace std;

int main()
{
    shared_ptr<Lexer> lexp = make_shared<Lexer>("getnextstatement.ple");
    FileStmtStream filess(lexp);
    shared_ptr<Statement> stp;

    require(
        filess.getNextStatement(stp),
        "Cannot get first statement");
    require(
        astType(stp, ProgramStmt),
        "First statement is not ProgramStmt");
    require(
        static_pointer_cast<ProgramStmt>(stp)->programName == "test",
        "Program name is not 'test'");

    require(
        filess.getNextStatement(stp),
        "Cannot get second statement");
    require(
        astType(stp, FunctionCallExpr),
        "Second statement is not FunctionCallExpr");
    shared_ptr<FunctionCallExpr> fcep =
        static_pointer_cast<FunctionCallExpr>(stp);
    require(
        fcep->callee.get() != nullptr,
        "Second statement does not have a Callee");
    require(
        astType(fcep->callee, VariableExpr),
        "Second statement's Callee is not VariableExpr");
    require(
        fcep->callee->token.content == "func",
        "Second statement's Callee is not 'func'");
    require(
        fcep->args.size() == 0,
        "Second statement has arguments");

    require(
        filess.getNextStatement(stp),
        "Cannot get third statement");
    require(
        astType(stp, FunctionCallExpr),
        "Third statement is not FunctionCallExpr");
    fcep = static_pointer_cast<FunctionCallExpr>(stp);
    require(
        fcep->callee.get() != nullptr,
        "Third statement does not have a Callee");
    require(
        astType(fcep->callee, VariableExpr),
        "Third statement's Callee is not VariableExpr");
    require(
        fcep->callee->token.content == "func2",
        "Third statement's Callee is not 'func2'");
    require(
        fcep->args.size() == 1,
        "Third statement does not have one argument");
    shared_ptr<Expression> arg0 = fcep->args[0];
    require(
        arg0.get() != nullptr,
        "Third statement's argument is null");
    require(
        astType(arg0, StringExpr),
        "Third statement's argument is not StringExpr");
    require(
        arg0->token.content == "\"aaa\"",
        "Third statement's argument is not 'aaa'");

    require(
        filess.getNextStatement(stp),
        "Cannot get fourth statement");
    require(
        astType(stp, FunctionCallExpr),
        "Fourth statement is not FunctionCallExpr");
    fcep = static_pointer_cast<FunctionCallExpr>(stp);
    require(
        fcep->callee.get() != nullptr,
        "Fourth statement does not have a Callee");
    require(
        astType(fcep->callee, VariableExpr),
        "Fourth statement's Callee is not VariableExpr");
    require(
        fcep->callee->token.content == "func3",
        "Fourth statement's Callee is not 'func3'");
    require(
        fcep->args.size() == 3,
        "Fourth statement does not have 3 arguments");
    arg0 = fcep->args[0];
    require(
        astType(arg0, VariableExpr),
        "Fourth statement's first argument is not VariableExpr");
    require(
        arg0->token.content == "wfwe",
        "Fourth statement's first argument is not 'wfwe'");
    require(
        astType(fcep->args[1], AddExpr),
        "Fourth statement's second argument is not AddExpr");
    shared_ptr<AddExpr> arg1 =
        static_pointer_cast<AddExpr>(fcep->args[1]);
    require(
        arg1->lhs.get() != nullptr,
        "Fourth statement's second argument does not have a left-hand side");
    require(
        arg1->rhs.get() != nullptr,
        "Fourth statement's second argument does not have a right-hand side");
    require(
        astType(arg1->lhs, VariableExpr),
        "Fourth statement's second argument LHS is not VariableExpr");
    require(
        arg1->lhs->token.content == "foo",
        "Fourth statement's second argument LHS is not 'foo'");
    require(
        astType(arg1->rhs, VariableExpr),
        "Fourth statement's second argument RHS is not VariableExpr");
    require(
        arg1->rhs->token.content == "bar",
        "Fourth statement's second argument RHS is not 'bar'");
    require(
        astType(fcep->args[2], FunctionCallExpr),
        "Fourth statement's third argument is not FunctionCallExpr");
    shared_ptr<FunctionCallExpr> arg2 =
        static_pointer_cast<FunctionCallExpr>(fcep->args[2]);
    require(
        arg2->callee.get() != nullptr,
        "Fourth statement's third argument does not have a Callee");
    require(
        astType(arg2->callee, VariableExpr),
        "Fourth statement's third argument's Callee is not VariableExpr");
    require(
        arg2->args.size() == 0,
        "Fourth statement's third argument has arguments");
    require(
        arg2->callee->token.content == "baz",
        "Fourth statement's third argument's Callee is not 'baz'");

    require(
        filess.getNextStatement(stp),
        "Cannot get fifth statement");
    require(
        astType(stp, VariableAssignExpr),
        "Fifth statement is not VariableAssignExpr");
    shared_ptr<VariableAssignExpr> vaep =
        static_pointer_cast<VariableAssignExpr>(stp);
    require(
        vaep->variable != nullptr,
        "Fifth statement does not have a Variable");
    require(
        vaep->value != nullptr,
        "Fifth statement does not have a Value");
    require(
        astType(vaep->variable, VariableExpr),
        "Fifth statement's Variable is not VariableExpr");
    require(
        vaep->variable->token.content == "_wr_func4",
        "Fifth statement's Variable is not '_wr_func4");
    require(
        astType(vaep->value, BlockExpr),
        "Fifth statement's Value is not BlockExpr");
    const shared_ptr<BlockExpr> blockp =
        static_pointer_cast<BlockExpr>(vaep->value);
    
    require(
        blockp->statements.size() == 3,
        "Block does not have 3 statements");
    require(
        astType(blockp->statements[0], AddExpr),
        "Block's first statement is not AddExpr");
    const shared_ptr<AddExpr> aep =
        static_pointer_cast<AddExpr>(blockp->statements[0]);
    require(
        aep->lhs != nullptr,
        "Block's first statement does not have a left-hand side");
    require(
        aep->rhs != nullptr,
        "Block's first statement does not have a right-hand side");
    require(
        astType(aep->lhs, StringExpr),
        "Block's first statement LHS is not StringExpr");
    require(
        aep->lhs->token.content == "\"aaa\"",
        "Block's first statement LHS is not '\"aaa\"'");
    require(
        astType(aep->rhs, StringExpr),
        "Block's first statement RHS is not StringExpr");
    require(
        aep->rhs->token.content == "\"bbb\"",
        "Block's first statement RHS is not '\"bbb\"'");

    require(
        astType(blockp->statements[1], FunctionCallExpr),
        "Block's second statement is not FunctionCallExpr");
    fcep = static_pointer_cast<FunctionCallExpr>(blockp->statements[1]);
    require(
        fcep->callee != nullptr,
        "Block's second statement does not have a Callee");
    require(
        astType(fcep->callee, VariableExpr),
        "Block's second statement's Callee is not VariableExpr");
    require(
        fcep->callee->token.content == "aaa",
        "Block's second statement's Calle is not 'aaa'");
    require(
        fcep->args.size() == 0,
        "Block's second statement has arguments");
    
    require(
        astType(blockp->statements[2], FunctionCallExpr),
        "Block's third statement is not FunctionCallExpr");
    fcep = static_pointer_cast<FunctionCallExpr>(blockp->statements[2]);
    require(
        fcep->callee != nullptr,
        "Block's third statement does not have a Callee");
    require(
        astType(fcep->callee, VariableExpr),
        "Block's third statement's Callee is not VariableExpr");
    require(
        fcep->callee->token.content == "bbb",
        "Block's third statement's Callee is not 'bbb'");
    require(
        fcep->args.size() == 1,
        "Block's third statement does not have 1 argument");
    require(
        astType(fcep->args[0], VariableExpr),
        "Block's third statement's argument is not VariableExpr");
    require(
        fcep->args[0]->token.content == "aaa",
        "Block's third statement's argument is not 'aaa'");

    require(
        !filess.getNextStatement(stp),
        "More than five statements have been read");

    return EXIT_SUCCESS;
}

