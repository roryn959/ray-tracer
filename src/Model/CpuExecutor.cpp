#include "Model/CpuExecutor.h"


CpuExecutor::CpuExecutor(const World& world) :
	m_world{world}
{}

void CpuExecutor::TraceRays(uint32_t* buffer) {
	for (int i = 0; i < NUM_PIXELS; ++i)
		TraceRay(buffer, i, m_world.GetBounds());
}

void CpuExecutor::TraceRay(uint32_t* buffer, size_t i, const WorldBounds& worldBounds) {
	//std::cout << "doing " << i << '\n';
	float x{0.0f};
	float y{0.0f};
	float z{0.0f};

	float xVelocity = ( ( (i % WINDOW_W) / static_cast<float>(WINDOW_W - 1) ) * 2 ) - 1;
	float yVelocity = ( ( (i / WINDOW_W) / static_cast<float>(WINDOW_H - 1) ) * -2 ) + 1;
	float zVelocity = 0.5f; // sqrt( 1 - (xVelocity * xVelocity) - (yVelocity * yVelocity) );

	float lowest_t{FLT_MAX};
	Colour colour{ 0, 0, 0, 255 };

	float t;

	// Left wall
	if (xVelocity < 0.0f) {
		t = (worldBounds.m_minX) / xVelocity;
		if (t < lowest_t) {
			colour = COLOUR_RED;
			lowest_t = t;
		}
	}

	// Right wall
	if (xVelocity > 0.0f) {
		t = (worldBounds.m_maxX - x) / xVelocity;
		if (t < lowest_t) {
			colour = COLOUR_BLUE;
			lowest_t = t;
		}
	}

	// Bottom wall
	if (yVelocity < 0.0f) {
		t = (worldBounds.m_minY - y) / yVelocity;
		if (t < lowest_t) {
			colour = COLOUR_GREEN;
			lowest_t = t;
		}
	}

	// Top wall
	if (yVelocity > 0.0f) {
		t = (worldBounds.m_maxY - y) / yVelocity;
		if (t < lowest_t) {
			colour = COLOUR_YELLOW;
			lowest_t = t;
		}
	}

	// Back wall
	if (zVelocity > 0.0f) {
		t = (worldBounds.m_maxZ - z) / zVelocity;
		if (t < lowest_t) {
			colour = COLOUR_TURQUOISE;
			lowest_t = t;
		}
	}

	buffer[i] = colour;
}