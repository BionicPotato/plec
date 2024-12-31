#include "test.hpp"
#include "../core/ast/ast.hpp"
#include "../core/ast/target.hpp"
#include <cstring>

int main()
{
    std::vector<const char*> astfns {"targets0.ple", "targets1.ple", "targets2.ple"};

    AST ast(std::move(astfns));
    ast.parse();
    ast.configure();

    require(
        ast.targets.size() == 1,
        "The number of targets created is other than 1");
    const Target* const targ = ast.targets[0].get();
    require(
        targ->name == "targets",
        "Target is not named 'targets'");
    require(
        targ->type == TARG_PROGRAM,
        "Target type is not program");
    require(
        targ->files.size() == 3,
        "Target does not have 3 files");
    require(
        strcmp(targ->files[0]->filename, "targets0.ple") == 0,
        "Target's first file is not named 'targets0.ple'");
    require(
        strcmp(targ->files[1]->filename, "targets1.ple") == 0,
        "Target's second file is not named 'targets1.ple'");
    require(
        strcmp(targ->files[2]->filename, "targets2.ple") == 0,
        "Targets's third file is not named 'targets2.ple'");

    return 0;
}
