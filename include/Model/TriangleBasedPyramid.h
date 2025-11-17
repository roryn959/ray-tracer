#pragma once

#include <cstddef>
#include <math.h>
#include <vector>

#include "Core/Colour.h"
#include "Core/Triangle.h"
#include "Core/Point.h"
#include "Model/Matrix.h"

class TriangleBasedPyramid {
public:
    /// @brief A triangle based pyramid
    /// @param p0 front base point
    /// @param p1 left base point
    /// @param p2 right base point
    /// @param p3 tip point
    /// @param colour colour of all sides
    TriangleBasedPyramid(Point p0, Point p1, Point p2, Point p3, Colour colour);

    inline Point operator[](size_t i) { return m_points[i]; }

    inline Colour GetColour() { return m_colour; }
    inline Point GetCentreOfMass() { return m_centreOfMass; }

    std::vector<Triangle> GetTriangles(); // Optimise this!!

    void ShiftX(float dx);
    void ShiftY(float dy);
    void ShiftZ(float dz);

    void RotateOnX(float theta);
    void RotateOnY(float theta);
    void RotateOnZ(float theta);

private:
    void UpdateTriangles();

    Point m_points[4];
    Point m_centreOfMass;
    const Colour m_colour;
    std::vector<Triangle> m_triangles;
};