#pragma once

#include "phragics/dep/glm/all.hpp"

namespace phragics::shading {

struct DirectionalLight {
    glm::packed_vec4 direction;
};

}
