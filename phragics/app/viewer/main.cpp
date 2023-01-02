#include <phragics/dep/glm/all.hpp>
#include <phragics/dep/glfw/all.hpp>
#include <phragics/dep/imgui/all.hpp>
#include <phragics/dep/std/filesystem/filesystem.hpp>
#include <phragics/common/os/breakpoint.hpp>

#include "application.hpp"

#include <cmath>
#include <vector>

using namespace phragics;

auto gl_debug_message_callback(
        GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    switch(source) {
    case GL_DEBUG_SOURCE_OTHER:
        return;
    }
    switch(type) {
    case GL_DEBUG_TYPE_OTHER:
    case GL_DEBUG_TYPE_PERFORMANCE:
        return;
    }
	if(source == GL_DEBUG_SOURCE_SHADER_COMPILER) {
		std::cout << message << std::endl;
	} else {
        // phragics::breakpoint();
        throw std::runtime_error(message);
    }
}



void throwing_main() {
    GLFWwindow* window;

    phragics::glfwInit();

    window = glfwCreateWindow(1280, 720, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(&gl_debug_message_callback, nullptr);

    imGuiSetup(*window);

    auto app = Application();
    app.window = window;

    while (!glfwWindowShouldClose(window))
    {
        imGuiNewFrame();

        app.update();

        ImGui::ShowDemoWindow();

        imGuiRender();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    imGuiCleanup();

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

auto main() -> int {
    try {
        throwing_main();
    } catch(const std::exception& e) {
        std::cerr << "std::exception: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unhandled exception." << std::endl;
    }
}
