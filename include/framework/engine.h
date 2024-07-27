#ifndef GHOSTGAME_ENGINE_H
#define GHOSTGAME_ENGINE_H

#include "framework/api.h"
#include "framework/renderer.h"
#include "framework/game.h"
#include "framework/entity.h"

#include <memory>
#include <unordered_map>

namespace GhostGame::Framework
{
    class GHOSTGAME_FRAMEWORK_API Engine {
    private:
        Renderer _renderer;

        std::unique_ptr<IGame> _game;

        std::unordered_map<int, Entity> _entities;

        float _lastTime = 0;

        EntityId _nextEntityId = 0;

    public:
        Engine();

        void start(std::unique_ptr<IGame>&& game);

        void processInput();

        void update();

        void stop();

        EntityId spawnEntity();

        void despawnEntity(EntityId id);

        Entity& getEntity(EntityId id);
    };
}


#endif