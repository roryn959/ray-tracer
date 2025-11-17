#pragma once

#include <vector>
#include <math.h>

#include "Core/Line.h"
#include "Core/Point.h"
#include "Core/Triangle.h"
#include "Canvas.h"

constexpr int GRAPH_HALFWIDTH = GRAPH_W / 2;
constexpr int GRAPH_HALFHEIGHT = GRAPH_H / 2;

constexpr float GRAPH_TO_WINDOW_WIDTH_FACTOR = WINDOW_W / (float) GRAPH_W;
constexpr float GRAPH_TO_WINDOW_HEIGHT_FACTOR = WINDOW_H / (float) GRAPH_H;

#define BACKGROUND_Z 100
#define SCREEN_Z 0.1f
#define FOV 1.0f

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

        void Set(int x, int y, float z, Colour colour) {
            if (z <= 0.01 || x < 0 || x >= m_width || y < 0 || y >= m_height) return;
            int position = Get1dPosition(x, y);
            if (z < m_distances[position]) {
                m_buffer[position] = colour;
                m_distances[position] = z;
            }
        }

        inline uint32_t* GetData() { return m_buffer.data(); }

        inline void ResetDistances() {
            //std::fill(m_distances.begin(), m_distances.end(), std::numeric_limits<float>::infinity());
            memset(m_distances.data(), 0x7F, m_buffer.size() * sizeof(float)); // Dirty undefined behavior >:)
        }

    private:
        int m_width;
        int m_height;

        std::vector<uint32_t> m_buffer;
        std::vector<float> m_distances;
    };

public:
    Paintbrush(Canvas& canvas);

    void Apply();

    void PaintBackground(Colour colour);
    void PaintAxes();

    void PaintPoint(Point point, Colour colour);
    void PaintLine(Line line, Colour colour);
    void PaintTriangle(const Triangle& triangle);

private:
    static inline int TranslateGraphToWindowX(float x) { return round((x + GRAPH_HALFWIDTH) * GRAPH_TO_WINDOW_WIDTH_FACTOR); };
    static inline int TranslateGraphToWindowY(float y) { return round(WINDOW_H - ((y + GRAPH_HALFHEIGHT) * GRAPH_TO_WINDOW_HEIGHT_FACTOR)); };
    static inline float TranslateGraphToWindowZ(float z) { return z; };

    inline void SetPaintColour(Colour colour) { SDL_SetRenderDrawColor(m_pRenderer, colour.m_red, colour.m_green, colour.m_blue, SDL_ALPHA_OPAQUE); }

    void Bresenham(int x0, int y0, int x1, int y1, Colour colour);

    inline int PinedaEdgeFunction(int px, int py, int v0x, int v0y, int v1x, int v1y) {
        return (py - v0y) * (v1x - v0x) - (px - v0x) * (v1y - v0y);
    }


    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;

    ZBuffer m_zBuffer;
};