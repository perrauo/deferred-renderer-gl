#include "framework/engine.h"

#include "GLFW/glfw3.h"

namespace GhostGame::Framework
{    
    Engine::Engine() {}

    void Engine::start(std::unique_ptr<IGame>&& game) 
    {
        _game = std::move(game);
        _game->start(*this);
    }

    void Engine::processInput() {
        // Implement your input processing logic here
    }

    void Engine::update() {

        float currentTime = glfwGetTime();
        double deltaTime = currentTime - _lastTime;
        _lastTime = currentTime;
        
        processInput();

        std::vector<EntityId> entitiesToErase;
        for (auto& [id, entity] : _entities) {
            entity.update(deltaTime);
            if (entity.markedForDeletion) {
                entitiesToErase.push_back(id);
            }
        }

        for (const auto& id : entitiesToErase) {
            _entities.erase(id);
        }

        _game->update(*this, deltaTime);

        _renderer.render();
    }

    void Engine::stop() {
    }

    void Engine::despawnEntity(EntityId id)
    {
        _entities.erase(id);
    }

    EntityId Engine::spawnEntity()
    {
        _entities.emplace(_nextEntityId);
        return _nextEntityId++;
    }

    Entity& Engine::getEntity(EntityId id)
    {
        auto it = _entities.find(id);
        if (it != _entities.end()) {
            return it->second;
        }
        else {
            
        }
    }
}