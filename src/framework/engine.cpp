#include "framework/engine.h"
#include "framework/entity.h"
#include "framework/renderer.h"
#include "framework/game.h"

#include "GLFW/glfw3.h"

namespace GhostGame::Framework
{    
    Engine::Engine(std::unique_ptr<Renderer>&& renderer)
    : _renderer(std::move(renderer))
    {
    }

    void Engine::start(std::unique_ptr<IGame>&& game) 
    {
        this->game = std::move(game);
        this->game->start(*this);
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
            
            for (auto& [typeidx, sys] : _systems)
            {
                sys->update(*this, entity, deltaTime);
            }

            if (entity.markedForDeletion) {
                entitiesToErase.push_back(id);
            }
        }

        game->update(*this, deltaTime);

        for (auto id : entitiesToErase)
        {
            _entities.erase(id);
        }

        _renderer->render();
    }

    void Engine::stop() {
    }

    Entity& Engine::spawnEntity()
    {
        return _entities[_nextEntityId++];
    }

    void Engine::despawnEntity(EntityId id)
    {
        _entities.erase(id);
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