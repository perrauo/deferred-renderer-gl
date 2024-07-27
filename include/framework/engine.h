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

    public:
        Engine();

        void Start(std::unique_ptr<IGame>&& game);

        void ProcessInput();

        void Update();

        void Stop();
    };
}


#endif