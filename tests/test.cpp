#include "test.hpp"
#include <iostream>

using namespace std;

bool _require(bool cond, string errorMessage)
{
    if (!cond) {
        std::cerr << errorMessage;
    }
    return cond;
}

