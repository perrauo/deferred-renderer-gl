#pragma once


#include "framework/types.h"
#include "framework/model.h"

namespace GhostGame::Framework
{
    class Engine;

    class Component {
    public :
        virtual void update(Engine& engine, float deltaTime) = 0;

        virtual ~Component() = default;
    };
}