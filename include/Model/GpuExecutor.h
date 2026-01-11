#pragma once
#include <cstddef>
#include <iostream>

#include "View/Canvas.h"
#include "Core/Colour.h"
#include "Ray.h"
#include "World.h"


class GpuExecutor {
public:
    GpuExecutor(const World& world);
    ~GpuExecutor();

    void TraceRays(uint32_t* data);

	void multiply_by_five(int* data, std::size_t count);

private:
	void InitialiseDevice();
	void InitialiseCommandQueue();
	void CheckCommandBuffer();
	void InitialisePipeline();

	const World& m_world;

    struct Impl;     // opaque
    Impl* impl;      // pimpl to hide Objective-C++
};
