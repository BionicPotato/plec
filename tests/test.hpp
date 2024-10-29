#pragma once

#include "../core/ast/statement.hpp"
#include <memory>
#include <typeinfo>

#define astType(stp, t) (_astType((stp), (typeid(t))))
#define require(cond, errorMessage) \
    if (!_require((cond), (errorMessage))) return EXIT_FAILURE

bool _astType(std::shared_ptr<Statement> stp, const std::type_info& t);
bool _require(bool cond, std::string errorMessage);

