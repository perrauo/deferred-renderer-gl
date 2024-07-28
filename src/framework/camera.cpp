#include "framework/camera.h"
#include "framework/engine.h"
#include "framework/renderer.h"
#include "framework/material.h"

namespace GhostGame::Framework
{
    void CameraComponent::start(Framework::Engine& engine, Framework::Entity& entity)
    {
        viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    }

    void CameraComponent::update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime)
    {       
        using namespace RenderPasses::Geometry;

        // Convert pitch, yaw and roll angles to radians
        float pitchRadians = glm::radians(pitch);
        float yawRadians = glm::radians(yaw);
        float rollRadians = glm::radians(roll);

        // Create a quaternion for each of the pitch, yaw and roll rotations
        glm::quat pitchQuat = glm::angleAxis(pitchRadians, glm::vec3(1, 0, 0));
        glm::quat yawQuat = glm::angleAxis(yawRadians, glm::vec3(0, 1, 0));
        glm::quat rollQuat = glm::angleAxis(rollRadians, glm::vec3(0, 0, 1));

        // Combine the pitch, yaw and roll rotations
        glm::quat combinedRotation = glm::normalize(pitchQuat * yawQuat * rollQuat);

        // Apply the combined rotation to the camera's view matrix
        viewMatrix = glm::mat4_cast(combinedRotation) * viewMatrix;

        engine.renderer->geometryRenderPass->material->setUniform(Uniforms::viewMatrix, viewMatrix);
    }
}