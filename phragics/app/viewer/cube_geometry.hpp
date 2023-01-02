#pragma once

#include <phragics/dep/glad/all.hpp>
#include <phragics/dep/glm/all.hpp>

#include <array>

namespace phragics {

struct CubeGeometry {
	GLuint indexBuffer = GL_NONE;
	GLuint vao = GL_NONE;
	GLuint vertexVBO = GL_NONE;
	GLuint normals = GL_NONE;

	GLsizei count = 0;
	GLenum type = GL_UNSIGNED_INT;

	CubeGeometry() {
		init();
	}

	void init() {
		{
			auto floats = std::array<float, 6 * 4 * 3>{
				// -X
				-1.f, +0.f, +0.f,
				-1.f, +0.f, +0.f,
				-1.f, +0.f, +0.f,
				-1.f, +0.f, +0.f,
				// -Y
				+0.f, -1.f, +0.f,
				+0.f, -1.f, +0.f,
				+0.f, -1.f, +0.f,
				+0.f, -1.f, +0.f,
				// -Z
				+0.f, +0.f, -1.f,
				+0.f, +0.f, -1.f,
				+0.f, +0.f, -1.f,
				+0.f, +0.f, -1.f,
				// +Z
				+0.f, +0.f, +1.f,
				+0.f, +0.f, +1.f,
				+0.f, +0.f, +1.f,
				+0.f, +0.f, +1.f,
				// +Y
				+0.f, +1.f, +0.f,
				+0.f, +1.f, +0.f,
				+0.f, +1.f, +0.f,
				+0.f, +1.f, +0.f,
				// +Z
				+1.f, +0.f, +0.f,
				+1.f, +0.f, +0.f,
				+1.f, +0.f, +0.f,
				+1.f, +0.f, +0.f,
			};
			glCreateBuffers(1, &normals);
			glNamedBufferStorage(normals,
								 sizeof(float) * size(floats),
								 data(floats),
								 GL_NONE);
		}
		{
			auto vertices = std::array<float, 6 * 4 * 3>{
				// -X
				-1.f, -1.f, -1.f,
				-1.f, -1.f, +1.f,
				-1.f, +1.f, +1.f,
				-1.f, +1.f, -1.f,
				// -Y
				-1.f, -1.f, -1.f,
				+1.f, -1.f, -1.f,
				+1.f, -1.f, +1.f,
				-1.f, -1.f, +1.f,
				// -Z
				-1.f, -1.f, -1.f,
				-1.f, +1.f, -1.f,
				+1.f, +1.f, -1.f,
				+1.f, -1.f, -1.f,
				// +Z
				-1.f, -1.f, +1.f,
				+1.f, -1.f, +1.f,
				+1.f, +1.f, +1.f,
				-1.f, +1.f, +1.f,
				// +Y
				-1.f, +1.f, -1.f,
				-1.f, +1.f, +1.f,
				+1.f, +1.f, +1.f,
				+1.f, +1.f, -1.f,
				// +X
				+1.f, -1.f, -1.f,
				+1.f, +1.f, -1.f,
				+1.f, +1.f, +1.f,
				+1.f, -1.f, +1.f,
			};
			glCreateBuffers(1, &vertexVBO);
			glNamedBufferStorage(vertexVBO,
				 sizeof(float) * size(vertices),
				 data(vertices),
				 GL_NONE);
		}
		{
			count = 2 * 3 * 6;
			auto triangles = std::array<GLuint, 36>{
				0, 1, 3, 1, 2, 3, // -X
				4, 5, 7, 5, 6, 7, // -Y
				8, 9, 11, 9, 10, 11, // -Z
				12, 13, 15, 13, 14, 15, // +Z
				16, 17, 19, 17, 18, 19, // +Y
				20, 21, 23, 21, 22, 23, // +X
			};
			type = GL_UNSIGNED_INT;
			glCreateBuffers(1, &indexBuffer);
			glNamedBufferStorage(indexBuffer,
								 sizeof(GLuint) * size(triangles),
								 data(triangles),
								 GL_NONE);
		}
		{
			glCreateVertexArrays(1, &vao);
			glVertexArrayElementBuffer(vao, indexBuffer);
			glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
			glVertexArrayVertexBuffer(vao, 0, vertexVBO, 0, 3 * sizeof(float));
			glVertexArrayAttribBinding(vao, 0, 0);
			glEnableVertexArrayAttrib(vao, 0);
			glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
			glVertexArrayVertexBuffer(vao, 1, normals, 0, 3 * sizeof(float));
			glVertexArrayAttribBinding(vao, 1, 1);
			glEnableVertexArrayAttrib(vao, 1);
		}
	}

	void render() {
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, count, type, 0);
	}
};

}