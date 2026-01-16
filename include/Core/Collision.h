#pragma once

#include "Core/Material.h"
#include "Core/Vector.h"

struct Collision {
	float 		m_t;
	Vector		m_normal;
	Vector		m_location;
	Material	m_material;
};