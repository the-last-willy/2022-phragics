#pragma once

#include "phragics/service/storage/interface.hpp"

#include <fstream>

namespace phragics::storage {

struct DefaultImplementation {
    struct Service {

    };

    struct Handle {
        auto operator->() -> Service* {
            return &service;
        }

        Service service;
    };
};

}