#pragma once

#include <cstdint>

struct Colour {
    float m_red;
    float m_green;
    float m_blue;
	float m_opacity;

    inline operator uint32_t() const {
        return 		( static_cast<int>(m_opacity)	<< 24 	)
		| 			( static_cast<int>(m_red) 		<< 16 	)
		| 			( static_cast<int>(m_green) 	<< 8	)
		| 			( static_cast<int>(m_blue)				);
    }
};

constexpr Colour COLOUR_BLACK 	{ 0, 	0, 		0, 		255 };
constexpr Colour COLOUR_WHITE 	{ 255,	255,	255, 	255 };
constexpr Colour COLOUR_RED 	{ 255,	0, 		0, 		255 };
constexpr Colour COLOUR_GREEN 	{ 0, 	255, 	0, 		255 };
constexpr Colour COLOUR_BLUE 	{ 0, 	0, 		255, 	255 };
constexpr Colour COLOUR_YELLOW 	{ 255, 	255, 	0, 		255 };
constexpr Colour COLOUR_PURPLE 	{ 255, 	0, 		255, 	255 };
constexpr Colour COLOUR_T		{ 0,	255,	255,	255 };