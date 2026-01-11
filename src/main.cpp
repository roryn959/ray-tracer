#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

#include "Core/Colour.h"

#define GPU_BUILD 0

#if GPU_BUILD
#include "Model/GpuExecutor.h"
typedef GpuExecutor Executor;
#else
#include "Model/CpuExecutor.h"
typedef CpuExecutor Executor;
#endif

#include "Model/World.h"
#include "View/Canvas.h"

void RenderScene(Canvas& canvas, CpuExecutor& executor) {
	uint32_t buffer[NUM_PIXELS];

	executor.TraceRays(buffer);
	canvas.ApplyPixels(buffer);
}

void Mainloop(Canvas& canvas, World& world, CpuExecutor& executor) {
	RenderScene(canvas, executor);

    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }
    }
}

int main() {
    Canvas canvas;
	World world;
	Executor executor(world);

	//gpu.multiply_by_five(data, 5);

    Mainloop(canvas, world, executor);

    return 0;
}
