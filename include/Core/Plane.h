#pragma once

#include "Core/Axis.h"
#include "Core/Material.h"

struct Plane {
	AXIS 		m_axis;
	float 		m_offset;
	Material	m_material;
};