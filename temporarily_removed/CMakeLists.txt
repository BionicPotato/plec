cmake_minimum_required(VERSION 3.20)
project(plec)

set(core_srcs

    core/ast/ast.cpp
    core/ast/ast.hpp
    core/ast/astvisitable.hpp
    core/ast/expression.cpp
    core/ast/expression.hpp
    core/ast/file.cpp
    core/ast/file.hpp
    core/ast/operatorexpression.hpp
    core/ast/program.hpp
    core/ast/statement.hpp
    core/ast/statementlist.cpp
    core/ast/statementlist.hpp
    core/ast/stringexpr.hpp
    core/ast/target.hpp
    core/ast/variableassignexpr.cpp
    core/ast/variableassignexpr.hpp
    core/ast/variableexpr.hpp
    core/exceptions/ambiguousstatement.cpp
    core/exceptions/ambiguousstatement.hpp
    core/exceptions/badassign.cpp
    core/exceptions/badassign.hpp
    core/exceptions/unexpectedtoken.cpp
    core/exceptions/unexpectedtoken.hpp
    core/exceptions/unknowntoken.cpp
    core/exceptions/unknowntoken.hpp
    core/visitors/ast/print.cpp
    core/visitors/ast/print.hpp
    core/visitors/astvisitor.hpp
    core/exceptions.cpp
    core/exceptions.hpp
    core/lexer.cpp
    core/lexer.hpp
    core/operators.cpp
    core/operators.hpp
    core/token.hpp
    core/tokenid.cpp
    core/tokenid.hpp
)

add_executable(plec plec.cpp ${core_srcs})