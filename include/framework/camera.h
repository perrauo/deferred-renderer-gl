#pragma once

#include "framework/entity.h"

#include <vector>
#include <memory>

namespace GhostGame::Framework
{
   
    class GHOSTGAME_FRAMEWORK_API CameraComponent : public Component {
    public:
        CameraComponent() = default;

        ~CameraComponent() = default;

        CameraComponent(const CameraComponent&) = default;
        CameraComponent& operator=(const CameraComponent&) = default;

        void update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
    };
}