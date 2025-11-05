#pragma once

#include <cstddef>

#include "Point.h"

struct Line {
    Point points[2];

    inline Point operator[](size_t i) {
        return points[i];
    }
};