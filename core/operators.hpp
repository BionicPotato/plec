#pragma once

#include <cstdint>
#include <utility>
#include "tokenid.hpp"

unsigned short getPrecedence(TokenID id);
bool isLeftAssociative(TokenID id);
std::pair<uint8_t, uint8_t> getValency(TokenID id);