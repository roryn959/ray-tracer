#pragma once

#include <vector>

#include "Core/Cuboid.h"
#include "Core/Plane.h"
#include "Core/Vector.h"


class World {
public:
	World();

	inline const std::vector<Cuboid>& 	GetCuboidLights() const { return m_cuboidLights; }
	inline const std::vector<Plane>&	GetPlanes() const { return m_planes; }
	inline const std::vector<Cuboid>& 	GetCuboids() const { return m_cuboids; }

private:
	std::vector<Cuboid>		m_cuboidLights;

	std::vector<Plane>		m_planes;
	std::vector<Cuboid> 	m_cuboids;
};