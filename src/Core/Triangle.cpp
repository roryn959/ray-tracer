#include "Core/Triangle.h"

Triangle::Triangle(Point p1, Point p2, Point p3, Colour colour) :
    m_points{p1, p2, p3},
    m_colour{colour}
{}

void Triangle::ShiftX(float dx) {
    m_points[0].m_x += dx;
    m_points[1].m_x += dx;
    m_points[2].m_x += dx;
}

void Triangle::ShiftY(float dy) {
    m_points[0].m_y += dy;
    m_points[1].m_y += dy;
    m_points[2].m_y += dy;
}

void Triangle::ShiftZ(float dz) {
    m_points[0].m_z += dz;
    m_points[1].m_z += dz;
    m_points[2].m_z += dz;
}
