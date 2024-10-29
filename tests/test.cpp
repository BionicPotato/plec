#include "test.hpp"
#include <iostream>

using namespace std;

bool _astType(shared_ptr<Statement> stp, const type_info& t)
{
    Statement* _s = stp.get();
    return typeid(*_s) == t;
}

bool _require(bool cond, string errorMessage)
{
    if (!cond) {
        std::cerr << errorMessage;
    }
    return cond;
}

