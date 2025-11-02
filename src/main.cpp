#include <SDL2/SDL.h>
#include <iostream>

#include "Core/Colour.h"
#include "View/Canvas.h"
#include "View/Paintbrush.h"

#define FRAME_RATE_FREQUENCY 50


void mainloop(Canvas& canvas, Paintbrush& paintbrush) {
    float lastTime = SDL_GetTicks() / 1000.0f;

    int frame_tick = FRAME_RATE_FREQUENCY;
    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        paintbrush.PaintBackground(COLOUR_WHITE);
        paintbrush.PaintAxes();

        paintbrush.PaintLine(Point{-20, 20, 5}, Point{25, -30, 7}, COLOUR_RED);

        paintbrush.Apply();

        --frame_tick;
        if (0 == frame_tick) {
            float currentTime = SDL_GetTicks() / 1000.0f;
            float fps = FRAME_RATE_FREQUENCY / (currentTime - lastTime);
            lastTime = currentTime;
            std::cout << "fps: " << fps << "\n";
            frame_tick = FRAME_RATE_FREQUENCY;
        }

    }
}

int main() {
    Canvas canvas;
    Paintbrush paintbrush(canvas);

    mainloop(canvas, paintbrush);

    return 0;
}
