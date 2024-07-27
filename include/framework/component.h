#pragma once

#include "framework/api.h"
#include "framework/types.h"

namespace GhostGame::Framework
{
    class Engine;

    class GHOSTGAME_FRAMEWORK_API Component {
    public :

        Component() = default;
        virtual ~Component() = default;

        virtual void update(Engine& engine, float deltaTime) = 0;
    };
}