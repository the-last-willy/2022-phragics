#pragma once

#include<functional>

namespace pcws {

// Nullable pointer.
template<typename T>
using NP = T*;

// Non-nullable pointer.
template<typename T>
using P = T*;

// Rebindable reference.
template<typename T>
using RebindableR = std::reference_wrapper<T>;

}
