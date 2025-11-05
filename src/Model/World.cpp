#include "Model/World.h"

World::World(Paintbrush& paintbrush) :
    m_paintbrush{paintbrush},
    m_triangles{}
{
    Triangle redTriangle{ { -40, 30, 1 }, { -5, 40, 1 }, { -15, -15, 1 }, COLOUR_RED };
    Triangle blueTriangle{ { -40, 30, 2 }, { -5, 40, 1.2 }, { -15, -15, 1.2 }, COLOUR_BLUE };

    m_triangles.push_back(redTriangle);
    m_triangles.push_back(blueTriangle);

    TriangleBasedPyramid tbp1{ {-10, -5, 1.5}, {10, 0, 2.5}, {30, 20, 1.5}, {15, 35, 1.75}, COLOUR_BLUE};
    m_triangleBasedPyramids.push_back(tbp1);
}

void World::Paint() {
    for (Triangle& triangle : m_triangles) 
        m_paintbrush.PaintTriangle(triangle);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids) {
        for (Triangle& triangle : triangleBasedPyramid.GetTriangles())
        {
            m_paintbrush.PaintTriangle(triangle);
        }
    }
}

void World::ProcessTimeTick(float dt) {
    m_triangles[0].ShiftZ(dt / 2.0f);
}