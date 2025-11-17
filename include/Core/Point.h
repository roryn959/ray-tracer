#pragma once

#include <iomanip>
#include <iostream>

struct Point {
    float m_x;
    float m_y;
    float m_z;

    Point operator+(const Point& rhs) const {
        return Point{ m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z };
    }

    Point operator-(const Point& rhs) const {
        return Point{ m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z };
    }
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << std::fixed << std::setprecision(3);
    os << "(" << std::setw(8) << p.m_x << ", "<< std::setw(8) << p.m_y << ", " << std::setw(8) << p.m_z << ")\n";
    return os;
}