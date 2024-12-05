#include "../visitors/astvisitor.hpp"
#include "target.hpp"

using namespace std;

Target::Target(const string& name, TargetType type)
: name(name), type(type) {}

void Target::accept(ASTVisitor& visitor) const
{
    visitor.doTarget(*this);
}

