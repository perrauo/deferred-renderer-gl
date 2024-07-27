#pragma once

#include "framework/api.h"

namespace GhostGame::Framework
{
    class Engine;

    class GHOSTGAME_FRAMEWORK_API IGame {
    public:
        virtual void Start(Engine& engine) = 0;
        virtual void Update(Engine& engine) = 0;
        virtual void Render(Engine& engine) = 0;
        virtual ~IGame() = default;
    };
}
