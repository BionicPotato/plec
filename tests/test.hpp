#pragma once

#include "../core/ast/statement.hpp"
#include <memory>
#include <typeinfo>

#define require(cond, errorMessage) \
    if (!_require((cond), (errorMessage))) return EXIT_FAILURE

bool _require(bool cond, std::string errorMessage);

