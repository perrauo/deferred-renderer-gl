#pragma once

#include "framework/engine.h"
#include "framework/entity.h"

#include <vector>
#include <memory>

#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Experiment::Framework
{
   
    class EXPERIMENT_FRAMEWORK_API CameraComponent : public Component {
    public:

        float pitch = 0.0f; // Up and down
        float yaw = 0.0f;   // Left and right
        float roll = 0.0f;  // Tilting head left and right

        CameraComponent() = default;

        ~CameraComponent() = default;

        CameraComponent(const CameraComponent&) = default;
        CameraComponent& operator=(const CameraComponent&) = default;

        void start(Framework::Engine& engine, Framework::Entity& entity);
        void update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;
        void draw(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) override;

        glm::vec3 getForward() const;
        glm::vec3 getUp() const;
    };
}