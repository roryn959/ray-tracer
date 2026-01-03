#include "Model/World.h"

World::World(Paintbrush& paintbrush) :
    m_paintbrush{paintbrush},
    m_triangles{},
    m_triangleBasedPyramids{},
    m_xVelocity{0},
    m_yVelocity{0},
    m_zVelocity{0}
{
    TriangleBasedPyramid tbp1{ {-1.75, 0, 2.5}, {-1.5, 0.25, 2.5}, {-1.25, 0, 2.5}, {-1.45, 0.05, 1.5}, COLOUR_GREEN};
    TriangleBasedPyramid tbp2{ {0.05, 0, 2.5}, {0.2, 0.25, 2.5}, {0.45, 0, 2.5}, {0.25, 0.05, 1.5}, COLOUR_GREEN};
    TriangleBasedPyramid tbp3{ {1.45, 0.05, 4}, {1.25, 0, 2.5}, {1.5, 0.25, 2.5}, {1.75, 0, 2.5}, COLOUR_GREEN};

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
    for (Triangle& triangle : m_triangles) 
       triangle.ShiftX(dx);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids)
        triangleBasedPyramid.ShiftX(dx);

}

void World::MovePovY(float dy) {
    for (Triangle& triangle : m_triangles) 
       triangle.ShiftY(dy);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids)
        triangleBasedPyramid.ShiftY(dy);

}

void World::MovePovZ(float dz) {
    for (Triangle& triangle : m_triangles) 
       triangle.ShiftZ(dz);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids)
        triangleBasedPyramid.ShiftZ(dz);

}

void World::ProcessTimeTick(float dt) {
    MovePovX(m_xVelocity * (dt / WORLD_SPEED));
    MovePovY(m_yVelocity * (dt / WORLD_SPEED));
    MovePovZ(m_zVelocity * (dt / WORLD_SPEED));
}

void World::MoveRight() {
    if (m_xVelocity == -1) return;
    m_xVelocity = 1;
}

void World::MoveLeft() {
    if (m_xVelocity == 1) return;
    m_xVelocity = -1;
}

void World::MoveForward() {
    if (m_zVelocity == -1) return;
    m_zVelocity = 1;
}

void World::MoveBackward() {
    if (m_zVelocity == 1) return;
    m_zVelocity = -1;
}

void World::MoveUp() {
    if (m_yVelocity == -1) return;
    m_yVelocity = 1;
}

void World::MoveDown() {
    if (m_yVelocity == 1) return;
    m_yVelocity = -1;
}

void World::UnMoveRight() {
    if (m_xVelocity == 1) m_xVelocity = 0;
}

void World::UnMoveLeft() {
    if (m_xVelocity == -1) m_xVelocity = 0;
}

void World::UnMoveForward() {
    if (m_zVelocity == 1) m_zVelocity = 0;
}

void World::UnMoveBackward() {
    if (m_zVelocity == -1) m_zVelocity = 0;
}

void World::UnMoveUp() {
    if (m_yVelocity == 1) m_yVelocity = 0;
}

void World::UnMoveDown() {
    if (m_yVelocity == -1) m_yVelocity = 0;
}