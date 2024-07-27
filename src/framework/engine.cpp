#include "framework/engine.h"

#include "GLFW/glfw3.h"

namespace GhostGame::Framework
{    
    Engine::Engine(std::unique_ptr<Renderer>&& renderer)
    : _renderer(std::move(renderer))
    {
    }

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
            entity.update(*this, deltaTime);
            if (entity.markedForDeletion) {
                entitiesToErase.push_back(id);
            }
        }

        for (const auto& id : entitiesToErase) {
            _entities.erase(id);
        }

        _game->update(*this, deltaTime);

        _renderer->render();
    }

    void Engine::stop() {
    }

    void Engine::despawnEntity(EntityId id)
    {
        _entities.erase(id);
    }

    std::pair<EntityId, Entity&> Engine::spawnEntity()
    {
        Entity& entity = _entities[_nextEntityId];
        return { _nextEntityId++, entity };
    }

    Entity& Engine::getEntity(EntityId id)
    {
        static Entity sInvalidEntity;

        auto it = _entities.find(id);
        if (it != _entities.end()) {
            return it->second;
        }
        else {
            return sInvalidEntity;
        }
    }
}