#include "asttype.hpp"

using namespace std;

bool _astType(const Statement* stp, const type_info& t)
{
    return typeid(*stp) == t;
}


