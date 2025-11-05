#pragma once

#include <cstddef>
#include <vector>

#include "Core/Colour.h"
#include "Core/Triangle.h"
#include "Core/Point.h"

class TriangleBasedPyramid {
public:
    TriangleBasedPyramid(Point p1, Point p2, Point p3, Point p4, Colour colour);

    inline Point operator[](size_t i) { return m_points[i]; }

    inline Colour GetColour() { return m_colour; }
    std::vector<Triangle> GetTriangles(); // Optimise this!!

    void ShiftX(float dx);
    void ShiftY(float dy);
    void ShiftZ(float dz);

private:
    Point m_points[4];
    Colour m_colour;
};