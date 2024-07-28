#pragma once

#include "framework/entity.h"

namespace GhostGame
{
    class Entity;

    // -------------------
    // EnemyComponent
    // -------------------

    class EnemyComponent : public Framework::Component
    {
    public:

        void update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
    };
}