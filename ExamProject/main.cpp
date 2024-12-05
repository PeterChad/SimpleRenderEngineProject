#include "sre/SDLRenderer.hpp"
#include <chrono>
#include <thread>

using namespace sre;

int main() {
    //Specifies the interval at which updates should occur. Here, it’s set for 60 updates per second.
    const double fixedTimeStep = 1.0 / 60.0; // 60 updates per second
    //Tracks the leftover time between updates to maintain consistent timing.
    double accumulator = 0.0;
    //Stores the time of the last iteration to calculate elapsed time in each frame.
    auto previousTime = std::chrono::high_resolution_clock::now();

    // Initializes the renderer, which sets up the rendering context and SDL dependencies.
    SDLRenderer renderer;
    //Prepares the rendering system. This is a SimpleRenderEngine abstraction that avoids manual SDL setup.
    renderer.init();

    // Placeholder for update logic
    auto update = [](double deltaTime) {
        // Perform game updates such as physics or state changes
        };

    // Set up the render function
    renderer.frameRender = [&]() {
        RenderPass rp = RenderPass::create().build();
        // Draw something (simple lines as an example)
        rp.drawLines({
            {-.5, -.5, 0},
            {.5, .5, 0},
            {-.5, .5, 0},
            {.5, -.5, 0}
            });
        };

    //Ensures the loop continues until the user exits.
    bool running = true;
    while (running) {
        //Records the current time at the start of the frame.
        auto currentTime = std::chrono::high_resolution_clock::now();
        //Calculates the time elapsed since the previous frame.
        std::chrono::duration<double> elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        // Adds the elapsed time to the accumulator, which tracks leftover time for updates.
        accumulator += elapsedTime.count();

        // Handle events (basic SDL2 events handling to allow quitting)
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Fixed time step update
        //Ensures the game logic is updated for each time step in the accumulator.
        while (accumulator >= fixedTimeStep) {
            //Calls the update function with a constant time step to keep updates consistent.
            update(fixedTimeStep);
            //Reduces the accumulator by the time step for each completed update.
            accumulator -= fixedTimeStep;
        }

        // Render a frame
        renderer.frameRender();
    }

    return 0;
}

//Notes from Peter:
//On line 62, why not set accumulator to 0?
//On line 43, why add things up like this instead of just checking previousTime vs currentTime? like: if (currentTime - previousTime > fixedTimeStep) {update}