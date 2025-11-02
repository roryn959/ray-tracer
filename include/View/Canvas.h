#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "Core/Colour.h"

#define WINDOW_W 800
#define WINDOW_H 800

#define GRAPH_W 100
#define GRAPH_H 100

class Canvas {
public:
    Canvas();
    ~Canvas();

    inline SDL_Window* GetWindow() { return m_pWindow; };
    inline SDL_Renderer* GetRenderer() { return m_pRenderer; };

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
};