#include "engine/engine.h"

namespace GhostGame
{    
    Engine::Engine() : isRunning(false) {}

    void Engine::Start() {
        isRunning = true;
        while (isRunning) {
            // Game loop
            ProcessInput();
            Update();
            renderer.Render();
        }
    }

    void Engine::ProcessInput() {
        // Implement your input processing logic here
    }

    void Engine::Update() {
        // Implement your game update logic here
    }

    void Engine::Stop() {
        isRunning = false;
    }
}