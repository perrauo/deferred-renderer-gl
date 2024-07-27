#pragma once

#include "framework/api.h"

namespace GhostGame::Framework
{
    class Engine;

    class GHOSTGAME_FRAMEWORK_API IGame {
    public:
        virtual void start(Engine& engine) = 0;
        virtual void update(Engine& engine, float deltaTime) = 0;
        virtual void render(Engine& engine) = 0;
        virtual ~IGame() = default;
    };
}
