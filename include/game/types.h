#pragma once

#include "framework/entity.h"

namespace GhostGame
{
    // -------------------
    // PlayerBehavior
    // -------------------

    class PlayerBehavior : public Framework::Component
    {
    public:
        PlayerBehavior();

        ~PlayerBehavior() override;

        void update(Framework::Engine& engine, float deltaTime) override;
    };

    // -------------------
    // EnemyBehavior
    // -------------------

    class EnemyBehavior : public Framework::Component
    {
    public:

        EnemyBehavior();

        ~EnemyBehavior() override;

        void update(Framework::Engine& engine, float deltaTime) override;
    };
}