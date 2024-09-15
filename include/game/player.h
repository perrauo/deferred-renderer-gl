#pragma once

#include "framework/entity.h"

namespace Framework::Framework
{
    class CameraComponent;
    using EntityId = int;
}

namespace Experiment::Demo
{
    // -------------------
    // PlayerComponent
    // -------------------

    class PlayerComponent : public Framework::Component
    {
    public:
        
        glm::vec2 lastCursorPos;

        void start(Framework::Engine& engine, Framework::Entity& entity) override;
        void update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
        void draw(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
    };
}