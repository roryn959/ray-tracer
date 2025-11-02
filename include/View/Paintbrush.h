#pragma once

#include "Core/Point.h"
#include "Canvas.h"

constexpr int GRAPH_HALFWIDTH = GRAPH_W / 2;
constexpr int GRAPH_HALFHEIGHT = GRAPH_H / 2;

constexpr float GRAPH_TO_WINDOW_WIDTH_FACTOR = WINDOW_W / (float) GRAPH_W;
constexpr float GRAPH_TO_WINDOW_HEIGHT_FACTOR = WINDOW_H / (float) GRAPH_H;

class Paintbrush {

    class ZBuffer {
    public:
        ZBuffer(int width, int height) :
            m_width{width},
            m_height{height},
            m_buffer(width * height),
            m_distances(width * height)
        {}

        inline int Get1dPosition(int x, int y) { return y * m_width + x; }

        inline void Set(int x, int y, float z, Colour colour) {
            m_buffer[y * m_width + x] = colour;

            int position = Get1dPosition(x, y);
            if (z < m_distances[position]) {
                m_buffer[position] = colour;
                m_distances[position] = z;
            }
        }

        inline uint32_t* GetData() { return m_buffer.data(); }

    private:
        int m_width;
        int m_height;

        std::vector<uint32_t> m_buffer;
        std::vector<float> m_distances;
    };

public:
    Paintbrush(Canvas& canvas);

    void Apply();

    void PaintBackground();
    void PaintBackground(Colour colour);

    void PaintLine(const Point& point, const Point& p2, Colour colour);

private:
    static inline int TranslateGraphToWindowX(float x) { return round((x + GRAPH_HALFWIDTH) * GRAPH_TO_WINDOW_WIDTH_FACTOR); };
    static inline int TranslateGraphToWindowY(float y) { return round(WINDOW_H - ((y + GRAPH_HALFHEIGHT) * GRAPH_TO_WINDOW_HEIGHT_FACTOR)); } ;

    inline void SetPaintColour(Colour colour) { SDL_SetRenderDrawColor(m_pRenderer, colour.m_red, colour.m_green, colour.m_blue, SDL_ALPHA_OPAQUE); }

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;

    ZBuffer m_zBuffer;
};