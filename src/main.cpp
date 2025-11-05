#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

#include "Core/Colour.h"
#include "Model/World.h"
#include "View/Canvas.h"
#include "View/Paintbrush.h"

#define FRAME_RATE_FREQUENCY 50


void mainloop(Canvas& canvas, Paintbrush& paintbrush) {
    World world{paintbrush};

    float lastTime = SDL_GetTicks() / 1000.0f;
    float lastFpsTime = lastTime;

    int frame_tick = FRAME_RATE_FREQUENCY;
    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Time-based processing
        float currentTime = SDL_GetTicks() / 1000.0f;
        float dt = currentTime - lastTime;

        world.ProcessTimeTick(dt);

        // Painting
        paintbrush.PaintBackground(COLOUR_WHITE);
        paintbrush.PaintAxes();

        world.Paint();

        paintbrush.Apply();


        // Calculate fps
        --frame_tick;
        if (0 == frame_tick) {
            float fps = FRAME_RATE_FREQUENCY / (currentTime - lastFpsTime);
            std::cout << "fps: " << fps << "\n";
            frame_tick = FRAME_RATE_FREQUENCY;
            lastFpsTime = currentTime;
        }

        lastTime = currentTime;
    }
}

int main() {
    Canvas canvas;
    Paintbrush paintbrush(canvas);

    mainloop(canvas, paintbrush);

    return 0;
}
