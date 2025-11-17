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
            m_zBuffer.Set(i, j, BACKGROUND_Z, colour);
        }
    }
}

void Paintbrush::PaintAxes() {
    for (int i=0; i<WINDOW_W; ++i) {
        m_zBuffer.Set(i, WINDOW_H / 2, 0.015f, COLOUR_BLACK);
    }

    for (int i=0; i<WINDOW_H; ++i) {
        m_zBuffer.Set(WINDOW_W / 2, i, 0.015f, COLOUR_BLACK);
    }
}

void Paintbrush::PaintPoint(Point point, Colour colour) {
    if (point.m_z < SCREEN_Z) return;

    m_zBuffer.Set(
        TranslateGraphToWindowX( point.m_x / (point.m_z * FOV) ),
        TranslateGraphToWindowY( point.m_y / (point.m_z * FOV) ),
        point.m_z, 
        colour
    );
}

void Paintbrush::PaintLine(Line line, Colour colour) {
    float z0 = line[0].m_z;
    float z1 = line[1].m_z;

    if (z0 < SCREEN_Z || z1 < SCREEN_Z) return;
    
    int x0 = TranslateGraphToWindowX(line[0].m_x / (z0 * FOV) );
    int y0 = TranslateGraphToWindowY(line[0].m_y / (z0 * FOV) );
    int x1 = TranslateGraphToWindowX(line[1].m_x / (z1 * FOV) );
    int y1 = TranslateGraphToWindowY(line[1].m_y / (z1 * FOV) );

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
        std::swap(z0, z1);
    }

    float dz = (z1 - z0);

    dz /= abs(steep ? dy : dx);
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;

    int y = y0;
    float z = z0;

    for (int x = x0; x <= x1; ++x) {
        if (steep)
            m_zBuffer.Set(y, x, TranslateGraphToWindowZ(z) - 0.01f, colour);
        else
            m_zBuffer.Set(x, y, TranslateGraphToWindowZ(z) - 0.01f, colour);

        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }

        z += dz;
    }
}

void Paintbrush::PaintTriangle(const Triangle& triangle) {
    Colour colour = triangle.GetColour();
    int red = colour.m_red;
    int green = colour.m_green;
    int blue = colour.m_blue;

    float v0z = triangle[0].m_z;
    float v1z = triangle[1].m_z;
    float v2z = triangle[2].m_z;

    if (v0z < SCREEN_Z || v1z < SCREEN_Z || v2z < SCREEN_Z) return;

    float tv0z = TranslateGraphToWindowZ(v0z);
    int v0x = TranslateGraphToWindowX(triangle[0].m_x / (v0z * 1));
    int v0y = TranslateGraphToWindowY(triangle[0].m_y / v0z);

    float tv1z = TranslateGraphToWindowZ(v1z);
    int v1x = TranslateGraphToWindowX(triangle[1].m_x / v1z);
    int v1y = TranslateGraphToWindowY(triangle[1].m_y / v1z);

    float tv2z = TranslateGraphToWindowZ(v2z);
    int v2x = TranslateGraphToWindowX(triangle[2].m_x / v2z);
    int v2y = TranslateGraphToWindowY(triangle[2].m_y / v2z);

    float area = PinedaEdgeFunction(v0x, v0y, v1x, v1y, v2x, v2y);

    if (area < 0) return;

    PaintLine( {triangle[0], triangle[1]}, COLOUR_BLACK );
    PaintLine( {triangle[1], triangle[2]}, COLOUR_BLACK );
    PaintLine( {triangle[2], triangle[0]}, COLOUR_BLACK );

    int min_x = std::min(v0x, v1x);
    min_x = std::min(min_x, v2x);

    int max_x = std::max(v0x, v1x);
    max_x = std::max(max_x, v2x);

    int min_y = std::min(v0y, v1y);
    min_y = std::min(min_y, v2y);

    int max_y = std::max(v0y, v1y);
    max_y = std::max(max_y, v2y);

    for (int i = min_x; i <= max_x; ++i) {
        for (int j = min_y; j <= max_y; ++j) {
            int w0 = PinedaEdgeFunction(i, j, v1x, v1y, v2x, v2y);
            int w1 = PinedaEdgeFunction(i, j, v2x, v2y, v0x, v0y);
            int w2 = PinedaEdgeFunction(i, j, v0x, v0y, v1x, v1y);

            if ((w0 > 0 && w1 > 0 && w2 > 0)) {
                float bv0 = w0 / area;
                float bv1 = w1 / area;
                float bv2 = w2 / area;

                float z = bv0 * tv0z + bv1 * tv1z + bv2 * tv2z;

                Colour shadedColour{ (int) (red * (bv0 + bv1)), (int) (green * (bv0 + bv1)), (int) (blue * (bv0 + bv1)) };
                m_zBuffer.Set(i, j, z, shadedColour);
            }
        }
    }
}