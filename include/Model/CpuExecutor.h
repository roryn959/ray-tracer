#pragma once

#include <cstddef>

#include "View/Canvas.h"
#include "Core/Colour.h"
#include "Ray.h"
#include "World.h"

class CpuExecutor {
public:
	CpuExecutor(const World& world);

	void TraceRays(uint32_t* buffer);

private:
	void TraceRay(uint32_t* buffer, size_t i, const WorldBounds& worldBounds);

	const World& m_world;
};