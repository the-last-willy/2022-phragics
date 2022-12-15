#pragma once

#include <phragics/common/gpu/all.hpp>
#include <phragics/dep/glm/all.hpp>

#include <optional>

namespace phragics {

class Geometry {
public:
    int vertex_count = 0;

	gpu::BufferHandle colors;
	gpu::BufferHandle indices;
	gpu::BufferHandle normals;
	gpu::BufferHandle positions;

    GLuint mode = GL_NONE;
};

}
