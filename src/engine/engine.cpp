#include "engine/engine.h"

namespace GhostGame
{    
    Engine::Engine() : _isRunning(false) {}

    void Engine::Start() {
        _isRunning = true;
        while (_isRunning) {
            // Game loop
            ProcessInput();
            Update();
            _renderer.Render();
        }
    }

    void Engine::ProcessInput() {
        // Implement your input processing logic here
    }

    void Engine::Update() {
        // Implement your game update logic here
    }

    void Engine::Stop() {
        _isRunning = false;
    }
}