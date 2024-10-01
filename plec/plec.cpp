//#include "core/cstnode.hpp"
#include "../core/lexer.hpp"
//#include "core/cst.hpp"
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

/*inline ifstream& openFile(ifstream& file, const char* s, const char*& filename)
{
    file.open(s);
    filename = s;
    return file;
}*/

/*void printTree(const CSTNode& node, unsigned indent=0)
{
    cout <<
        string("ID: ").insert(0, indent, '\t') << getTokenIDString(node.token.id) <<
        "; val: " << +node.lhs << '/' << +node.rhs <<
        "; " << node.token.filename << ':' << node.token.lineNo << ':' << node.token.charNo <<
        "; content: \"" << node.token.content << "\"" <<
        endl;
    
    if (!node.LHSChildren.empty()) {
        cout << string("LHS:\n").insert(0, indent, '\t');
        for (CSTNode* child : node.LHSChildren) {
            printTree(*child, indent+1);
        }
    }

    if (!node.RHSChildren.empty()) {
        cout << string("RHS:\n").insert(0, indent, '\t');
        for (CSTNode* child : node.RHSChildren) {
            printTree(*child, indent+1);
        }
    }
}*/

int main(int argc, char** argv)
{
    int exitCode = EXIT_SUCCESS;
    cout.sync_with_stdio(false);
    //ifstream infile;
    //const char* filename = "stdin";
    //istream& input = (argc > 1) ? openFile(infile, argv[1], filename) : cin;
    //Lexer lex(input, filename);

    //Lexer lex((argc > 1) ? argv[1] : "");

    vector<const char*> astfns;
    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(fs::current_path())) {
	const char* c = entry.path().filename().c_str();
	char* n = new char[strlen(c)];
	strcpy(n, c);
        astfns.push_back(n);
    }

    //AST ast((argc > 1) ? vector<const char*>(&argv[1], &argv[argc]) : vector<const char*>({""}));
    AST ast(astfns);
    try {
        ast.parse();
        ast.prerun();
	ast.accept(ASTPrintVisitor::instance());
    } catch (exception& e) {
        cerr << e.what() << endl;
	exitCode = EXIT_FAILURE;
    }

    for (const char* s : astfns) {
	delete s;
    }
    /*CST cst;
    while (cst.addNode(lex.getNextToken())) {}
    try {
        cst.parse();
    } catch (UnexpectedTokenException e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    for (CSTNode* nodeptr : cst.topNodes) {
        printTree(*nodeptr);
    }*/

    return exitCode;
}
