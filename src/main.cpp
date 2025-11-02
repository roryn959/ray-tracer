#include <SDL2/SDL.h>
#include <iostream>

#include "Core/Colour.h"
#include "View/Canvas.h"
#include "View/Paintbrush.h"

void mainloop(Canvas& canvas, Paintbrush& paintbrush) {
    float lastTime = SDL_GetTicks() / 1000.0f;

    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        paintbrush.PaintBackground(COLOUR_WHITE);

        paintbrush.PaintLine(Point{-50, -50}, Point{50, 50}, COLOUR_RED);

        paintbrush.Apply();

        float currentTime = SDL_GetTicks() / 1000.0f;
        float fps = 1 / (currentTime - lastTime);
        lastTime = currentTime;

        std::cout << "fps: " << fps << "\n";

    }
}

int main() {
    Canvas canvas;
    Paintbrush paintbrush(canvas);

    mainloop(canvas, paintbrush);

    return 0;
}
