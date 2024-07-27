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
        ~PlayerBehavior() override {
        }

        virtual void update(Framework::Engine& engine, float deltaTime) override;
    };

    // -------------------
    // EnemyBehavior
    // -------------------

    class EnemyBehavior : public Framework::Component
    {
    public:

        ~EnemyBehavior() override {
        }

        virtual void update(Framework::Engine& engine, float deltaTime) override;
    };
}