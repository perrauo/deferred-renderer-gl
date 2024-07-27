#ifndef GHOSTGAME_ENGINE_H
#define GHOSTGAME_ENGINE_H

#include "framework/api.h"
#include "framework/renderer.h"
#include "framework/game.h"
#include "framework/entity.h"

#include <memory>

namespace GhostGame::Framework
{
    class GHOSTGAME_FRAMEWORK_API Engine {
    private:
        Renderer _renderer;
        bool _isRunning;

        std::unique_ptr<IGame> _game;

        std::vector<std::unique_ptr<Entity>> _entities;

        std::vector<std::unique_ptr<Entity>> _entities;

    public:
        Engine();

        void start(std::unique_ptr<IGame>&& game);

        void processInput();

        void update();

        void stop();

        void add(std::unique_ptr<Entity>&& entity);
    };
}


#endif