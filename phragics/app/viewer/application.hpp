#pragma once

#include "config.hpp"
#include "cube_geometry.hpp"

#include <phragics/dep/glm/all.hpp>
#include <phragics/dep/std/filesystem/filesystem.hpp>

#include <GLFW/glfw3.h>

#include <array>

namespace phragics {

struct Background {
	GLuint vertexShader = GL_NONE;
	GLuint fragmentShader = GL_NONE;
	GLuint program = GL_NONE;
	GLuint vao = GL_NONE;
	GLuint vbo = GL_NONE;

	GLuint count = 0;

	glm::mat4 uniformV = glm::mat4(1.);

	Background() {}

	void init() {
		{
			{
				auto data = std::array<float, 2 * 3 * 3>{
					-1.f, -1.f, +1.f,
					+1.f, -1.f, +1.f,
					-1.f, +1.f, +1.f,
					-1.f, +1.f, +1.f,
					+1.f, -1.f, +1.f,
					+1.f, +1.f, +1.f,
				};
				count = 6;
				glCreateBuffers(1, &vbo);
				glNamedBufferStorage(vbo, sizeof(float) * size(data), std::data(data), GL_NONE);
			}
			{
				glCreateVertexArrays(1, &vao);
				glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
				glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
				glVertexArrayAttribBinding(vao, 0, 0);
				glEnableVertexArrayAttrib(vao, 0);
			}
		}

		reload();
	}

	void reload() {
		{
			{
				vertexShader = glCreateShader(GL_VERTEX_SHADER);
				auto str = phragics_std::file_to_string(
					projectPath + "phragics/shading/background.vert");
				auto data = str.c_str();
				glShaderSource(vertexShader, 1, &data, nullptr);
				glCompileShader(vertexShader);
				GLint status;
				glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
				if(status == GL_FALSE) {
					vertexShader = GL_NONE;
				}
			}
			{
				fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				auto str = phragics_std::file_to_string(
					projectPath + "phragics/shading/background.frag");
				auto data = str.c_str();
				glShaderSource(fragmentShader, 1, &data, nullptr);
				glCompileShader(fragmentShader);
				GLint status;
				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
				if(status == GL_FALSE) {
					fragmentShader = GL_NONE;
				}
			}
			if(vertexShader != GL_NONE && fragmentShader != GL_NONE) {
				program = glCreateProgram();
				glAttachShader(program, vertexShader);
				glAttachShader(program, fragmentShader);
				glLinkProgram(program);
				GLint status;
				glGetProgramiv(program, GL_LINK_STATUS, &status);
				if(status == GL_FALSE) {
					program = GL_NONE;
				}
			} else {
				program = GL_NONE;
			}
		}
	}

	void update() {
//		if(ImGui::IsKeyDown(ImGuiKey_R)) {
//			std::cout << "--Reloading shaders" << std::endl;
//			reload();
//		}
	}

	void render() {
		if(program != GL_NONE) {
			glUseProgram(program);
			glDisable(GL_DEPTH_TEST);
			glBindVertexArray(vao);
			glProgramUniformMatrix4fv(program, 0, 1, GL_FALSE, &uniformV[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	}
};

struct Camera {
    float heading = 0.f;
    float pitch = 0.f;
    float roll = 0.f;

    glm::vec4 position = glm::vec4(0.f, 0.f, 0.f, 1.f);
    float speed = 0.1f;

    float forwardMovement = 0.f;
    float lateralMovement = 0.f;

    glm::mat4 uniformN = glm::mat4(1.f);
    glm::mat4 uniformP = glm::mat4(1.f);
    glm::mat4 uniformV = glm::mat4(1.f);

    void update() {
        {
			forwardMovement = 0.f;
			lateralMovement = 0.f;
            auto& io = ImGui::GetIO();
            if(!io.WantCaptureKeyboard) {
                if(ImGui::IsKeyDown(ImGuiKey_W)) {
                    forwardMovement -= 1.f;
                }
                if(ImGui::IsKeyDown(ImGuiKey_S)) {
                    forwardMovement += 1.f;
                }
                if(ImGui::IsKeyDown(ImGuiKey_A)) {
                    lateralMovement -= 1.f;
                }
                if(ImGui::IsKeyDown(ImGuiKey_D)) {
                    lateralMovement += 1.f;
                }
            }
            if(!io.WantCaptureMouse) {
                if(ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
                    auto dt = io.MouseDelta;
                    heading += -dt[0] / 1000.f;
                    pitch -= -dt[1] / 1000.f;
                }
            }
        }
        {
            auto headingAxis = glm::vec3(0.f, -1.f, 0.f);
            auto headingMat = glm::rotate(heading, headingAxis);
            auto pitchAxis = glm::vec3(1.f, 0.f, 0.f);
            auto pitchMat = glm::rotate(pitch, pitchAxis);
            auto rollAxis = glm::vec3(0.f, 0.f, -1.f);
            auto rollMat = glm::rotate(roll, rollAxis);
            uniformV = rollMat * pitchMat * headingMat;
            uniformN = glm::inverse(glm::transpose(uniformV));

            uniformP = glm::perspective(90.f, 16.f/9.f, 0.1f, 1000.f);

            glm::vec4 movement = speed * glm::inverse(uniformV) * glm::vec4(lateralMovement, 0.f, forwardMovement, 0.f);
            position += glm::vec4(movement.x, movement.y, movement.z, 0.f);
			uniformV = uniformV * glm::translate(glm::vec3(-position));
        }
    }
};

struct Cube {
    GLuint indexBuffer = GL_NONE;
    GLuint vao = GL_NONE;
    GLuint verticesVBO = GL_NONE;
    GLuint normals = GL_NONE;
    GLsizei count = 0;
    GLenum type = GL_UNSIGNED_INT;

    GLuint vertexShader = GL_NONE;
    GLuint fragmentShader = GL_NONE;
    GLuint program = GL_NONE;

    glm::mat4 uniformM = glm::mat4(1.f);
    glm::mat4 uniformN = glm::mat4(1.f);
    glm::mat4 uniformP = glm::mat4(1.f);
    glm::mat4 uniformV = glm::mat4(1.f);
	glm::vec3 uniformColor = glm::vec3(1.f);

    Cube() {
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
            glCreateBuffers(1, &verticesVBO);
            glNamedBufferStorage(verticesVBO,
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
            glVertexArrayVertexBuffer(vao, 0, verticesVBO, 0, 3 * sizeof(float));
            glVertexArrayAttribBinding(vao, 0, 0);
            glEnableVertexArrayAttrib(vao, 0);
			glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
			glVertexArrayVertexBuffer(vao, 1, normals, 0, 3 * sizeof(float));
			glVertexArrayAttribBinding(vao, 1, 1);
			glEnableVertexArrayAttrib(vao, 1);
        }
        {
            {
                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                auto str = phragics_std::file_to_string(
					projectPath + "phragics/shading/cube.vert");
                auto data = str.c_str();
                glShaderSource(vertexShader, 1, &data, nullptr);
                glCompileShader(vertexShader);
            }
            {
                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                auto str = phragics_std::file_to_string(
					projectPath + "phragics/shading/cube.frag");
                auto data = str.c_str();
                glShaderSource(fragmentShader, 1, &data, nullptr);
                glCompileShader(fragmentShader);
            }
            {
                program = glCreateProgram();
                glAttachShader(program, vertexShader);
                glAttachShader(program, fragmentShader);
                glLinkProgram(program);
            }
        }
    }

    void render() {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
        glUseProgram(program);
        glProgramUniformMatrix4fv(program, 0, 1, GL_FALSE, &uniformM[0][0]);
        glProgramUniformMatrix4fv(program, 4, 1, GL_FALSE, &uniformN[0][0]);
        glProgramUniformMatrix4fv(program, 8, 1, GL_FALSE, &uniformP[0][0]);
        glProgramUniformMatrix4fv(program, 12, 1, GL_FALSE, &uniformV[0][0]);
        glProgramUniformMatrix4fv(program, 12, 1, GL_FALSE, &uniformV[0][0]);
        glProgramUniform3fv(program, 13, 1,&uniformColor[0]);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, count, type, 0);
    }
};

struct Basis {
	std::array<Cube, 3> axes;
	float length = 1.f;
	float width = 0.1f;

	glm::mat4 uniformN = glm::mat4(1.);
	glm::mat4 uniformP = glm::mat4(1.);
	glm::mat4 uniformV = glm::mat4(1.);

	Basis() {}

	void init() {
		auto s0 = width / 2.f;
		auto s1 = (length + width) / 2.f;;
		auto t0 = 0.f;
		auto t1 = length / 2.f;
		axes[0].uniformColor = glm::vec3(1.f, 0.f, 0.f);
		axes[0].uniformM = glm::translate(glm::vec3(t1, t0, t0)) * glm::scale(glm::vec3(s1, s0, s0));
		axes[1].uniformColor = glm::vec3(0.f, 1.f, 0.f);
		axes[1].uniformM = glm::translate(glm::vec3(t0, t1, t0)) * glm::scale(glm::vec3(s0, s1, s0));
		axes[2].uniformColor = glm::vec3(0.f, 0.f, 1.f);
		axes[2].uniformM = glm::translate(glm::vec3(t0, t0, t1)) * glm::scale(glm::vec3(s0, s0, s1));
	}

	void render() {
		for(auto& axis : axes) {
			axis.uniformN = uniformN;
			axis.uniformP = uniformP;
			axis.uniformV = uniformV;
			axis.render();
		}
	}
};

struct Sphere {
	CubeGeometry cubeGeom;

	GLuint vertexShader = GL_NONE;
	GLuint fragmentShader = GL_NONE;
	GLuint program = GL_NONE;

	glm::mat4 u_M = glm::mat4(1.f);
	glm::mat4 u_P = glm::mat4(1.f);
	glm::mat4 u_V = glm::mat4(1.f);

	glm::vec3 u_center = glm::vec3(0.);
	float u_radius = 1.f;

	Sphere() {}

	void init() {
		u_V = glm::translate(u_center) * glm::scale(glm::vec3(u_radius));

		reload();
	}

	void reload() {
		{
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			auto str = phragics_std::file_to_string(
				projectPath + "phragics/shading/sphere.vert");
			auto data = str.c_str();
			glShaderSource(vertexShader, 1, &data, nullptr);
			glCompileShader(vertexShader);
			GLint status;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
			if(status == GL_FALSE) {
				vertexShader = GL_NONE;
			}
		}
		{
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			auto str = phragics_std::file_to_string(
				projectPath + "phragics/shading/sphere.frag");
			auto data = str.c_str();
			glShaderSource(fragmentShader, 1, &data, nullptr);
			glCompileShader(fragmentShader);
			GLint status;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
			if(status == GL_FALSE) {
				fragmentShader = GL_NONE;
			}
		}
		if(vertexShader != GL_NONE && fragmentShader != GL_NONE) {
			program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);
			GLint status;
			glGetProgramiv(program, GL_LINK_STATUS, &status);
			if(status == GL_FALSE) {
				program = GL_NONE;
			}
		} else {
			program = GL_NONE;
		}
	}

	void update() {
		if(ImGui::IsKeyReleased(ImGuiKey_R)) {
			std::cout << "--Reloading shaders" << std::endl;
			reload();
		}
	}

	void render() {
		if(program != GL_NONE) {
			glUseProgram(program);
			cubeGeom.render();
		}
	}
};

struct Application {
    GLFWwindow* window = nullptr;

	Background background;
    Camera camera;
    Cube cube;
	Sphere sphere;
	Basis basis;

    Application() {
        init();
    }

    void init() {
		background.init();
		basis.init();
    }

    void update() {
        glClearColor(0.f, 0.f, 0.f, 1.f);
		glClearDepth(1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		background.update();
        camera.update();
		sphere.update();

		background.uniformV = camera.uniformV;
		background.render();

		sphere.u_V = camera.uniformV;
		sphere.u_P = camera.uniformP;
		sphere.render();

        basis.uniformN = camera.uniformN;
		basis.uniformP = camera.uniformP;
		basis.uniformV = camera.uniformV;
        basis.render();

        if(ImGui::Begin("Infos")) {
            ImGui::Text("HPR = (%f, %f, %f)",
                camera.heading, camera.pitch, camera.roll);
            ImGui::Text("POS = (%f, %f, %f, %f)",
                camera.position[0], camera.position[1], camera.position[2], camera.position[3]);
        }
        ImGui::End();
    }
};

}