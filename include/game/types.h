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
        void start(Framework::Engine& engine, Framework::Entity& entity) override;
        void update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
        void draw(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
    };
}