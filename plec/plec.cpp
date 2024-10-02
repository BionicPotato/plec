#include "../core/lexer.hpp"
#include "../core/exceptions.hpp"
#include "../core/tokenid.hpp"
#include "../core/ast/ast.hpp"
#include "../core/visitors/ast/print.hpp"
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

int main(int argc, char** argv)
{
    int exitCode = EXIT_SUCCESS;
    cout.sync_with_stdio(false);

    vector<const char*> astfns;
    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(fs::current_path())) {
	const char* c = entry.path().filename().c_str();
	char* n = new char[strlen(c)];
	strcpy(n, c);
        astfns.push_back(n);
    }

    AST ast(astfns);
    try {
        ast.parse();
        ast.configure();
	ast.accept(ASTPrintVisitor::instance());
    } catch (exception& e) {
        cerr << e.what() << endl;
	exitCode = EXIT_FAILURE;
    }

    for (const char* s : astfns) {
	delete s;
    }

    return exitCode;
}

