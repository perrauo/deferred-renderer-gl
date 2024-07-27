#pragma once

#include "framework/api.h"
#include "framework/renderer.h"
#include "framework/game.h"
#include "framework/entity.h"

#include <memory>
#include <unordered_map>
#include <utility> // pair
#include <functional> // reference_wrapper

namespace GhostGame::Framework
{
    using EntityId = int;

    class GHOSTGAME_FRAMEWORK_API Engine {
    private:       
        std::unique_ptr<IGame> _game;

        std::unordered_map<EntityId, Entity> _entities;

        std::unique_ptr<Renderer> _renderer;

        float _lastTime = 0;

        EntityId _nextEntityId = 0;

    public:
        Engine(std::unique_ptr<Renderer>&& renderer);        

        void start(std::unique_ptr<IGame>&& game);

        void processInput();

        void update();

        void stop();

        std::pair<EntityId, Entity&> spawnEntity();

        void despawnEntity(EntityId id);

        Entity& getEntity(EntityId id);
    };
}
