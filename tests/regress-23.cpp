#include "../core/ast/statement.hpp"
#include "../core/stmtstreams/file.hpp"
#include "../core/lexer.hpp"
#include "../core/exceptions/ambiguousstatement.hpp"
#include <memory>

using namespace std;

// The bug turned out to happen whenever an exception occurs during the execution of StatementStream::getExpression
// So this test should test for getExpression causing a crash when throwing *any* exception
// So it shouldn't actually rely on a TOK_NUMBER being present, because these will eventually get added to the language and not cause an error anymore
// Ambiguous statements are a reliable way of causing a parsing error, so this is what this test is testing
int main()
{
    shared_ptr<Lexer> lexp = make_shared<Lexer>("regress-23.ple");
    FileStmtStream filess(lexp);
    unique_ptr<const Statement> stp;

    try {
        filess.getNextStatement(stp);
    } catch (AmbiguousStatementException& e) {
        return EXIT_SUCCESS;
    }
}

