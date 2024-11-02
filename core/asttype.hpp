#pragma once

#include "ast/statement.hpp"
#include <memory>
#include <typeinfo>

#define astType(stp, t) (_astType((stp), (typeid(t))))

bool _astType(std::shared_ptr<Statement> stp, const std::type_info& t);

