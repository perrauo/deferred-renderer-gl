#include "framework/engine.h"

namespace GhostGame::Framework
{    
    Engine::Engine() : _isRunning(false) {}

    void Engine::Start(std::unique_ptr<IGame>&& game) 
    {
        _isRunning = true;
        _game = std::move(game);
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