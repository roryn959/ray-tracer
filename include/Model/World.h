#pragma once

#include <vector>

#include "Core/Triangle.h"
#include "TriangleBasedPyramid.h"
#include "View/Paintbrush.h"

#define WORLD_SPEED 1.0

class World {
public:
    World(Paintbrush& paintbrush);

    void Paint();

    void MovePovX(float dx);
    void MovePovY(float dy);
    void MovePovZ(float dz);

    void ProcessTimeTick(float dt);

    void MoveRight();
    void MoveLeft();
    void MoveForward();
    void MoveBackward();
    void MoveUp();
    void MoveDown();

    void UnMoveRight();
    void UnMoveLeft();
    void UnMoveForward();
    void UnMoveBackward();
    void UnMoveUp();
    void UnMoveDown();

private:
    Paintbrush&                         m_paintbrush;

    std::vector<Triangle>               m_triangles;
    std::vector<TriangleBasedPyramid>   m_triangleBasedPyramids;

    float                               m_xVelocity;
    float                               m_yVelocity;
    float                               m_zVelocity;    

};