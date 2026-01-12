#include <metal_stdlib>
using namespace metal;

#define WINDOW_W 700
#define WINDOW_H 700


struct WorldBounds {
	float m_minX;
	float m_maxX;
	float m_minY;
	float m_maxY;
	float m_minZ;
	float m_maxZ;
	float m_pad0;
	float m_pad1;
};

kernel void TraceRay(
    device uint* buffer [[ buffer(0) ]],
	constant WorldBounds& worldBounds [[buffer(1)]],
    uint i [[ thread_position_in_grid ]]
) {
	const float FLT_INF = as_type<float>(0x7F7FFFFF);

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	float xVelocity = ( ( (i % WINDOW_W) / float(WINDOW_W - 1) ) * 2 ) - 1;
	float yVelocity = ( ( (i / WINDOW_W) / float(WINDOW_H - 1) ) * -2 ) + 1;
	float zVelocity = 0.5f;

	float lowest_t{FLT_INF};
	uint colour;

	float t;

	// Left wall
	if (xVelocity < 0.0f) {
		t = (worldBounds.m_minX) / xVelocity;
		if (t < lowest_t) {
			colour = 0xFFFF0000;
			lowest_t = t;
		}
	}

	// Right wall
	if (xVelocity > 0.0f) {
		t = (worldBounds.m_maxX - x) / xVelocity;
		if (t < lowest_t) {
			colour = 0xFF0000FF;
			lowest_t = t;
		}
	}

	// Bottom wall
	if (yVelocity < 0.0f) {
		t = (worldBounds.m_minY - y) / yVelocity;
		if (t < lowest_t) {
			colour = 0xFFFF00FF;
			lowest_t = t;
		}
	}

	// Top wall
	if (yVelocity > 0.0f) {
		t = (worldBounds.m_maxY - y) / yVelocity;
		if (t < lowest_t) {
			colour = 0xFFFFFF00;
			lowest_t = t;
		}
	}

	// Back wall
	if (zVelocity > 0.0f) {
		t = (worldBounds.m_maxZ - z) / zVelocity;
		if (t < lowest_t) {
			colour = 0xFF00FFFF;
			lowest_t = t;
		}
	}

	buffer[i] = colour;

}
