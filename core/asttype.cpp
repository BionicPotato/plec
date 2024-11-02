#include "asttype.hpp"

using namespace std;

bool _astType(shared_ptr<Statement> stp, const type_info& t)
{
    Statement* _s = stp.get();
    return typeid(*_s) == t;
}

