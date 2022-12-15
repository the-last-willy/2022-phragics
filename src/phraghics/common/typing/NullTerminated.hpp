#pragma once

namespace phragics {

template<typename T>
using NullTerminated = T;

using ZString = NullTerminated<const char*>;

}