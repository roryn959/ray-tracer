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

    m_zBuffer.ResetDistances();
}

void Paintbrush::PaintBackground(Colour colour) {
    for (int j=0; j<WINDOW_H; ++j) {
        for (int i=0; i<WINDOW_W; ++i) {
            m_zBuffer.Set(i, j, 1000, colour);
        }
    }
}

void Paintbrush::PaintAxes() {
    for (int i=0; i<WINDOW_W; ++i) {
        m_zBuffer.Set(i, WINDOW_H / 2, 10, COLOUR_BLACK);
    }

    for (int i=0; i<WINDOW_H; ++i) {
        m_zBuffer.Set(WINDOW_W / 2, i, 10, COLOUR_BLACK);
    }
}

void Paintbrush::PaintPoint(Point point, Colour colour) {
    m_zBuffer.Set(
        TranslateGraphToWindowX(point.m_x / point.m_z),
        TranslateGraphToWindowY(point.m_y / point.m_z),
        point.m_z, 
        colour
    );
}

void Paintbrush::PaintLine(const Point& p1, const Point& p2, Colour colour) {
    float x0 = TranslateGraphToWindowX(p1.m_x);
    float y0 = TranslateGraphToWindowY(p1.m_y);
    float x1 = TranslateGraphToWindowX(p2.m_x);
    float y1 = TranslateGraphToWindowY(p2.m_y);

    int dx = x1 - x0;
    int dy = y1 - y0;
    
    bool steep = abs(dy) > abs(dx);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    dx = x1 - x0;
    dy = abs(y1 - y0);
    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for (int x = x0; x <= x1; ++x) {
        if (steep)
            m_zBuffer.Set(y, x, p1.m_z, colour);
        else
            m_zBuffer.Set(x, y, p1.m_z, colour);

        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }

}