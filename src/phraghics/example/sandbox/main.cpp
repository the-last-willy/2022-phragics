#include <phraghics/dep/glfw/all.hpp>
#include <phraghics/dep/glm/all.hpp>

#include <cmath>
#include <vector>

namespace phragics {}

using namespace phragics;

auto gl_debug_message_callback(
        GLenum source, GLenum type, GLuint id,
       GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    __debugbreak();
    throw std::runtime_error(message);
}



void throwing_main() {
    GLFWwindow* window;

    phragics::glfwInit();

    window = glfwCreateWindow(1600, 900, "Simple example", NULL, NULL);
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

    auto app = Application();

	glfwSwapBuffers(window);

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
