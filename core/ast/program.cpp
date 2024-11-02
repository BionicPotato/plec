#include "program.hpp"
#include "targettype.hpp"

using namespace std;

Program::Program(const string& name)
: Target(name, TARG_PROGRAM) {}

