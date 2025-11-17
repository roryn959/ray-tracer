#include "Model/TriangleBasedPyramid.h"

TriangleBasedPyramid::TriangleBasedPyramid(Point p0, Point p1, Point p2, Point p3, Colour colour) :
    m_points{p0, p1, p2, p3},
    m_centreOfMass{ 0, 0, 0 },
    m_colour{colour},
    m_triangles{}
{
    m_triangles.push_back({ m_points[0], m_points[2], m_points[1], m_colour});
    m_triangles.push_back({ m_points[0], m_points[1], m_points[3], m_colour });
    m_triangles.push_back({ m_points[1], m_points[2], m_points[3], m_colour });
    m_triangles.push_back({ m_points[0], m_points[3], m_points[2], m_colour });
    
    for (const Point& point : m_points) {
        m_centreOfMass.m_x += point.m_x;
        m_centreOfMass.m_y += point.m_y;
        m_centreOfMass.m_z += point.m_z;
    }

    m_centreOfMass.m_x /= 4.0f;
    m_centreOfMass.m_y /= 4.0f;
    m_centreOfMass.m_z /= 4.0f;
}

std::vector<Triangle> TriangleBasedPyramid::GetTriangles() {
    UpdateTriangles();
    return m_triangles;
}

void TriangleBasedPyramid::UpdateTriangles() {
    m_triangles[0] = Triangle{ m_points[0], m_points[2], m_points[1], m_colour };
    m_triangles[1] = Triangle{ m_points[0], m_points[1], m_points[3], m_colour };
    m_triangles[2] = Triangle{ m_points[1], m_points[2], m_points[3], m_colour };
    m_triangles[3] = Triangle{ m_points[0], m_points[3], m_points[2], m_colour };
}

void TriangleBasedPyramid::ShiftX(float dx) {
    for (Point &point : m_points)
        point.m_x += dx;

    m_centreOfMass.m_x += dx;
}

void TriangleBasedPyramid::ShiftY(float dy) {
    for (Point &point : m_points)
        point.m_y += dy;

    m_centreOfMass.m_y += dy;
}

void TriangleBasedPyramid::ShiftZ(float dz) {
    for (Point &point : m_points)
        point.m_z += dz;

    m_centreOfMass.m_z += dz;
}

void TriangleBasedPyramid::RotateOnX(float theta) {
    float c = std::cos(theta), s = std::sin(theta);

    Matrix<float, 3, 3> Rx{
        { 1, 0, 0 },
        { 0, c, -s },
        { 0, s, c }
    };

    for (int i = 0; i < 4; ++i) {
        Point &point = m_points[i];
        point = point - m_centreOfMass;
        point = Rx * point;
        point = point + m_centreOfMass;
    }
}

void TriangleBasedPyramid::RotateOnY(float theta) {

    float c = std::cos(theta), s = std::sin(theta);

    Matrix<float, 3, 3> Ry{
        { c, 0, s },
        { 0, 1, 0 },
        { -s, 0, c}
    };

    for (int i = 0; i < 4; ++i) {
        Point &point = m_points[i];
        point = point - m_centreOfMass;
        point = Ry * point;
        point = point + m_centreOfMass;
    }

}

void TriangleBasedPyramid::RotateOnZ(float theta) {
    float c = std::cos(theta), s = std::sin(theta);

    Matrix<float, 3, 3> Rz{
        { c, s, 0 },
        { -s, c, 0 },
        { 0, 0, 1 }
    };

    for (int i = 0; i < 4; ++i) {
        Point &point = m_points[i];
        point = point - m_centreOfMass;
        point = Rz * point;
        point = point + m_centreOfMass;
    }

}