#include "Model/World.h"

World::World(Paintbrush& paintbrush) :
    m_paintbrush{paintbrush},
    m_triangles{},
    m_triangleBasedPyramids{}
{
    TriangleBasedPyramid tbp1{ {-1.75, 0, 2.5}, {-1.5, 0.25, 2.5}, {-1.25, 0, 2.5}, {-1.45, 0.05, 1.5}, COLOUR_GREEN};
    TriangleBasedPyramid tbp2{ {0.05, 0, 2.5}, {0.2, 0.25, 2.5}, {0.45, 0, 2.5}, {0.25, 0.05, 1.5}, COLOUR_GREEN};
    TriangleBasedPyramid tbp3{ {1.45, 0.05, 1.5}, {1.25, 0, 2.5}, {1.5, 0.25, 2.5}, {1.75, 0, 2.5}, COLOUR_GREEN};

    m_triangleBasedPyramids.push_back(tbp1);
    m_triangleBasedPyramids.push_back(tbp2);
    m_triangleBasedPyramids.push_back(tbp3);
}

void World::Paint() {
    for (Triangle& triangle : m_triangles) 
        m_paintbrush.PaintTriangle(triangle);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids) {

        for (const Triangle& triangle : triangleBasedPyramid.GetTriangles()) 
            m_paintbrush.PaintTriangle(triangle);
    }
}

void World::MovePovX(float dx) {
    dx *= -1;

    for (Triangle& triangle : m_triangles) 
       triangle.ShiftX(dx);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids)
        triangleBasedPyramid.ShiftX(dx);

}

void World::MovePovY(float dy) {
    dy *= -1;

    for (Triangle& triangle : m_triangles) 
       triangle.ShiftY(dy);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids)
        triangleBasedPyramid.ShiftY(dy);

}

void World::MovePovZ(float dz) {
    dz *= -1;

    for (Triangle& triangle : m_triangles) 
       triangle.ShiftZ(dz);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids)
        triangleBasedPyramid.ShiftZ(dz);

}

void World::ProcessTimeTick(float dt) {

    m_triangleBasedPyramids[0].RotateOnY(M_PI * (dt / 3.0f));
    m_triangleBasedPyramids[1].RotateOnZ(M_PI * (dt / 10.0f));
    m_triangleBasedPyramids[2].RotateOnY(M_PI * (dt / 10.0f));

    MovePovX(dt / 10.0f);
    MovePovY(dt / 10.0f);
}