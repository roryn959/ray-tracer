#pragma once

#include "Core/Material.h"
#include "Core/Vector.h"


struct Cuboid {
	Vector 		m_min;
	Vector 		m_max;
	Material 	m_material;
};

inline Vector GetCentre(const Cuboid& c) {
	return Vector{ (c.m_max.m_x + c.m_min.m_x) / 2.0f, (c.m_max.m_y + c.m_min.m_y) / 2.0f, (c.m_max.m_z + c.m_min.m_z) / 2.0f };
}