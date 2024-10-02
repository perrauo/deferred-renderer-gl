#pragma once

#include "framework/engine.h"
#include "framework/entity.h"

namespace Framework::Framework
{
    class CameraComponent;
    ;
}

namespace Experiment::Demo
{
    // -------------------
    // PlayerComponent
    // -------------------

    class PlayerComponent : public Framework::Component
    {
    public:
        
        float movementSpeed = 10.0f;
        glm::vec2 lastCursorPos;

        void start(Framework::Engine& engine, Framework::Entity& entity) override;
        void update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
        void draw(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
    };
}