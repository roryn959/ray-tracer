#include "Model/TriangleBasedPyramid.h"

TriangleBasedPyramid::TriangleBasedPyramid(Point p1, Point p2, Point p3, Point p4, Colour colour) :
    m_points{p1, p2, p3, p4},
    m_colour{colour}
{}

std::vector<Triangle> TriangleBasedPyramid::GetTriangles() {
    std::vector<Triangle> triangles;
    triangles.push_back({ m_points[2], m_points[1], m_points[0], m_colour });
    triangles.push_back({ m_points[0], m_points[1], m_points[3], m_colour });
    triangles.push_back({ m_points[1], m_points[2], m_points[3], m_colour });
    triangles.push_back({ m_points[0], m_points[2], m_points[3], m_colour });
    return triangles;
}

void TriangleBasedPyramid::ShiftX(float dx) {
    m_points[0].m_x += dx;
    m_points[1].m_x += dx;
    m_points[2].m_x += dx;
    m_points[3].m_x += dx;
}

void TriangleBasedPyramid::ShiftY(float dy) {
    m_points[0].m_y += dy;
    m_points[1].m_y += dy;
    m_points[2].m_y += dy;
    m_points[3].m_y += dy;
}

void TriangleBasedPyramid::ShiftZ(float dz) {
    m_points[0].m_z += dz;
    m_points[1].m_z += dz;
    m_points[2].m_z += dz;
    m_points[3].m_z += dz;
}