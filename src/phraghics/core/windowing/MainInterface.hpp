#pragma once

#include "phragics/core/windowing/GpuManager.hpp"

#include <phragics/common/typing/all.hpp>
#include <phragics/dep/imgui/all.hpp>

#include <functional>
#include <string>

namespace phragics::windowing {

class Context;

enum class OpenFileStatus {
	undefined,

	found,
	notFound,

	count
};

struct OpenFileResult {
	OpenFileStatus status = {};
};

class MainInterface {

public:
	GpuManager gpuManager;

	bool hasFailedToFindFile = false;

	std::function<OpenFileResult(NullTerminated<const char*>)> onOpenFile
	= [](NullTerminated<const char*>) { return OpenFileResult(); };
};

void update(MainInterface&, Context&);

}

#include "phragics/core/windowing/context.hpp"
