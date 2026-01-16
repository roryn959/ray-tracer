#pragma once

#include "Core/Colour.h"
#include "Core/Vector.h"

struct Ray {
	Vector m_pos;
	Vector m_vel;
	Colour m_colour;
};