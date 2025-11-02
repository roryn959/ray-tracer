#include "View/Paintbrush.h"

Paintbrush::Paintbrush(Canvas& canvas) :
    m_pWindow{canvas.GetWindow()},
    m_pRenderer{canvas.GetRenderer()},
    m_pTexture{},
    m_zBuffer(WINDOW_W, WINDOW_H)
{
    m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_W, WINDOW_H);
}

void Paintbrush::Apply() {
    SDL_UpdateTexture(m_pTexture, nullptr, m_zBuffer.GetData(), WINDOW_W * sizeof(uint32_t));
    SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, nullptr);
    SDL_RenderPresent(m_pRenderer);
}

void Paintbrush::PaintBackground() {
    PaintBackground(COLOUR_WHITE);
}

void Paintbrush::PaintBackground(Colour colour) {
    for (int j=0; j<WINDOW_H; ++j) {
        for (int i=0; i<WINDOW_W; ++i) {
            m_zBuffer.Set(i, j, 1000, colour);
        }
    }
}

void Paintbrush::PaintLine(const Point& p1, const Point& p2, Colour colour) {
    float dx = p2.m_x - p1.m_x;
    float dy = p2.m_y - p1.m_y;

    int NUM_STEPS = 1000;
    dx = dx / NUM_STEPS;
    dy = dy / NUM_STEPS;

    float cx = p1.m_x;
    float cy = p1.m_y;
    for (int i=0; i<NUM_STEPS; ++i) {
        m_zBuffer.Set(TranslateGraphToWindowX(cx), TranslateGraphToWindowY(cy), 5, colour);
        cx += dx;
        cy += dy;
    }
}