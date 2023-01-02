#include "interface.hpp"

#include "phragics/common/default.hpp"

#include <chrono>

using namespace phragics;

namespace timing {

template<> auto API<Default>::Now::get() -> std::time_t {
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}

}