#pragma once

#include "impl.hpp"

namespace phragics::storage {

using DefaultAPI = API<DefaultImplementation>;

template<> auto DefaultAPI::create(std::filesystem::path) const -> FileId {

}

}