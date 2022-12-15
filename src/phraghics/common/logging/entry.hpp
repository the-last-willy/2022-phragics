#pragma once

#include "phragics/common/logging/timestamp.hpp"

namespace phragics::log {

class Entry {
public:
	Timestamp timestamp;

	std::string message;
};

}
