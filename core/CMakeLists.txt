cmake_minimum_required(VERSION 3.20)
project(plec-core)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX .db)
endif()

add_library(plec-core SHARED
    ast/addexpr.cpp
    ast/addexpr.hpp
    ast/arrayexpr.cpp
    ast/arrayexpr.hpp
    ast/ast.cpp
    ast/ast.hpp
    ast/astvisitable.hpp
    ast/blockexpr.cpp
    ast/blockexpr.hpp
    ast/expression.cpp
    ast/expression.hpp
    ast/file.cpp
    ast/file.hpp
    ast/functioncallexpr.cpp
    ast/functioncallexpr.hpp
    ast/operatorexpression.hpp
    ast/program.cpp
    ast/program.hpp
    ast/programstmt.cpp
    ast/programstmt.hpp
    ast/statement.cpp
    ast/statement.hpp
    ast/statementlist.cpp
    ast/statementlist.hpp
    ast/stringexpr.hpp
    ast/target.cpp
    ast/target.hpp
    ast/targettype.cpp
    ast/targettype.hpp
    ast/variableassignexpr.cpp
    ast/variableassignexpr.hpp
    ast/variableexpr.hpp
    exceptions/ambiguousstatement.cpp
    exceptions/ambiguousstatement.hpp
    exceptions/badassign.cpp
    exceptions/badassign.hpp
    exceptions/badcall.cpp
    exceptions/badcall.hpp
    exceptions/unexpectedtoken.cpp
    exceptions/unexpectedtoken.hpp
    exceptions/unknownfilename.cpp
    exceptions/unknownfilename.hpp
    exceptions/unknowntoken.cpp
    exceptions/unknowntoken.hpp
    runners/astconfigure.cpp
    runners/astconfigure.hpp
    stmtstreams/block.cpp
    stmtstreams/block.hpp
    stmtstreams/file.cpp
    stmtstreams/file.hpp
    visitors/ast/print.cpp
    visitors/ast/print.hpp
    visitors/astvisitor.hpp
    exceptions.cpp
    exceptions.hpp
    expressionparsing.cpp
    expressionparsing.hpp
    lexer.cpp
    lexer.hpp
    runner.hpp
    statementstream.cpp
    statementstream.hpp
    token.hpp
    tokenid.cpp
    tokenid.hpp
)

install(TARGETS plec-core RUNTIME DESTINATION bin LIBRARY DESTINATION lib)
