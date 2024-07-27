#include "framework/engine.h"

namespace GhostGame::Framework
{    
    Engine::Engine() : _isRunning(false) {}

    void Engine::start(std::unique_ptr<IGame>&& game) 
    {
        _isRunning = true;
        _game = std::move(game);
        _game->start(*this);
        while (_isRunning) {
            // Game loop
            processInput();
            update();
            _renderer.render();
        }
    }

    void Engine::processInput() {
        // Implement your input processing logic here
    }

    void Engine::update() {
        // Implement your game update logic here
    }

    void Engine::stop() {
        _isRunning = false;
    }
}