#pragma once

#include "framework/api.h"

namespace GhostGame::Framework
{
    class Engine;

    class GHOSTGAME_FRAMEWORK_API IGame {
    public:
        virtual void start(Engine& engine) {}
        virtual void update(Engine& engine, float deltaTime) {}
        virtual void draw(Engine& engine, float deltaTime) {}
    };
}
