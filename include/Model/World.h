#pragma once

#include <vector>

#include "Core/Triangle.h"
#include "TriangleBasedPyramid.h"
#include "View/Paintbrush.h"

class World {
public:
    World(Paintbrush& paintbrush);

    void Paint();

    void MovePovX(float dx);
    void MovePovY(float dy);
    void MovePovZ(float dz);

    void ProcessTimeTick(float dt);

private:
    Paintbrush& m_paintbrush;

    std::vector<Triangle> m_triangles;
    std::vector<TriangleBasedPyramid> m_triangleBasedPyramids;

};