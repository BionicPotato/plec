#pragma once

#include "ast/statement.hpp"
#include <memory>
#include <typeinfo>

#define astType(stp, t) (_astType((stp).get(), (typeid(t))))

bool _astType(const Statement* stp, const std::type_info& t);

template<class T, class U>
std::unique_ptr<T> moveCast(std::unique_ptr<U>& p)
{
    T* tp = static_cast<T*>(p.release());
    return std::unique_ptr<T>(tp);
}

