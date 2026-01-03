#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

#include "Core/Colour.h"
#include "Model/World.h"
#include "View/Canvas.h"
#include "View/Paintbrush.h"

#define FRAME_RATE_FREQUENCY 50

void handle_keydown(World& world, SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_a:
            world.MoveRight();
            break;
        
        case SDLK_d:
            world.MoveLeft();
            break;

        case SDLK_w:
            world.MoveBackward();
            break;

        case SDLK_s:
            world.MoveForward();
            break;
        
        case SDLK_q:
            world.MoveUp();
            break;
        
        case SDLK_e:
            world.MoveDown();
            break;
        
        default:
            break;
    }
}

void handle_keyup(World& world, SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_a:
            world.UnMoveRight();
            break;
        
        case SDLK_d:
            world.UnMoveLeft();
            break;

        case SDLK_w:
            world.UnMoveBackward();
            break;

        case SDLK_s:
            world.UnMoveForward();
            break;
        
        case SDLK_q:
            world.UnMoveUp();
            break;
        
        case SDLK_e:
            world.UnMoveDown();
            break;
        
        default:
            break;
    }
}

void mainloop(Canvas& canvas, Paintbrush& paintbrush) {
    World world{paintbrush};

    float lastTime = SDL_GetTicks() / 1000.0f;
    float lastFpsTime = lastTime;

    int frame_tick = FRAME_RATE_FREQUENCY;
    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                
                case SDL_KEYDOWN:
                    handle_keydown(world, event);
                    break;
                
                case SDL_KEYUP:
                    handle_keyup(world, event);
                    break;
                
                default:
                    break;
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
