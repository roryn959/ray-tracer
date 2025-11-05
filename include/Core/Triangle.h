#pragma once

#include <cstddef>

#include "Colour.h"
#include "Point.h"

class Triangle {
public:
    Triangle(Point p1, Point p2, Point p3, Colour colour);

    inline Point operator[](size_t i) { return m_points[i]; }

    inline Colour GetColour() { return m_colour; }

    void ShiftX(float dx);
    void ShiftY(float dy);
    void ShiftZ(float dz);

private:
    Point m_points[3];
    Colour m_colour;
};