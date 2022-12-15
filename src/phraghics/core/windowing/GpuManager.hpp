#pragma once

#include <phragics/common/gpu/context/context.hpp>

namespace phragics::windowing {

class Context;

class GpuManager {
public:
	gpu::Context* context = nullptr;

	bool isOpened = false;
};

void update(GpuManager&, Context&);

void updateObjects(GpuManager&, Context&);

void updateObjectsBuffers(GpuManager&);
void updateObjectsPrograms(GpuManager&);
void updateObjectsTextures(GpuManager&, Context&);

}

#include "phragics/core/windowing/context.hpp"
