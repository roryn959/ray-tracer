#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <math.h>

#define GPU_BUILD 1

#if GPU_BUILD
#include "Model/GpuExecutor.h"
typedef GpuExecutor Executor;
#else
#include "Model/CpuExecutor.h"
typedef CpuExecutor Executor;
#endif

#include "Model/World.h"
#include "View/Canvas.h"

typedef std::chrono::high_resolution_clock hrc;


void RenderScene(Canvas& canvas, Executor& executor, uint32_t* buffer) {
	executor.TraceRays(buffer);
	canvas.ApplyPixels(buffer);
}

void Mainloop(Canvas& canvas, World& world, Executor& executor) {
	uint32_t buffer[NUM_PIXELS];

	std::chrono::time_point<hrc> start, end;
	std::chrono::duration<float> duration;

	start = hrc::now();
	RenderScene(canvas, executor, buffer);
	end = hrc::now();

	duration = end - start;
	float s = duration.count();
	std::cout << "Initial render took " << s << " seconds.\n";

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

		RenderScene(canvas, executor, buffer);
    }
}

int main() {
    Canvas canvas;
	World world;
	Executor executor(world);

    Mainloop(canvas, world, executor);

    return 0;
}
