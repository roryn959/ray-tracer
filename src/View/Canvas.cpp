#include "View/Canvas.h"

Canvas::Canvas() :
    m_pWindow{},
    m_pRenderer{}
{
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
        std::exit(-1);
    }

    m_pWindow = SDL_CreateWindow("Rasteriser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);

    if (NULL == m_pWindow) {
        std::cout << "Failed to create window\n";
        std::exit(-1);
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == m_pRenderer) {
        std::cout << "Failed to create renderer\n";
        std::exit(-1);
    }

    SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

    
}

Canvas::~Canvas() {
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}