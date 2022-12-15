#include <phragics/common/file/all.hpp>
#include <phragics/core/windowing/all.hpp>
#include <phragics/dep/glfw/all.hpp>
#include <phragics/dep/imgui/all.hpp>
#include <phragics/dep/stb/all.hpp>

#include <array>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>

using namespace phragics;

auto gl_debug_message_callback(
	GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	__debugbreak();
	throw std::runtime_error(message);
}

struct Application {
	GLFWwindow* window = nullptr;

	file::System fileSystem;

	windowing::FileManager fileManager;
	windowing::OpenFileDialog openFileDialog;

	Application();

	void update();
};

Application::Application() {
	fileManager.fileSystem_ = &fileSystem;
	openFileDialog.fileSystem_ = &fileSystem;
}

void Application::update() {
	glClear(GL_COLOR_BUFFER_BIT);

	if(ImGui::BeginMainMenuBar()) {

		ImGui::EndMainMenuBar();
	}

	windowing::update(fileManager);
	windowing::update(openFileDialog);
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
