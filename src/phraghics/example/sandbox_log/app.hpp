#pragma once

#include "log_manager.hpp"

#include <phragics/common/communicating/all.hpp>
#include <phragics/common/logging/all.hpp>

#include <phragics/dep/glfw/all.hpp>
#include <phragics/dep/imgui/all.hpp>

using namespace phragics;

struct LogMediator {

};

struct LoggingContext {
	com::LinkEnd<log::Entry> logEntry;
};

struct UserInterfaceContext {
	com::LinkEnd<log::Entry> logExit;
};

struct Application {
	GLFWwindow* window = nullptr;

	Log log_;

	LogTestWindow logTestWindow_;
	LogViewer logWindow_;


	com::Emitter<> clearLogsEmitter_;

	Application();

	void update();
};

Application::Application() {
	logTestWindow_.onLog = [this](const LogEntry& entry) {
		this->log_.add(entry);
	};
	logWindow_.log_ = &log_;
}

void Application::update() {
	glClear(GL_COLOR_BUFFER_BIT);

	if(auto mainMenuBar = ImGui_::ScopedMainMenuBar()) {

	}

	logTestWindow_.update();
	logWindow_.update();

	logWindow_.onClear = [ptr = &log_](){ ptr->clear(); };
}
