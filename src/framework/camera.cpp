#include "framework/camera.h"
#include "framework/engine.h"
#include "framework/renderer.h"
#include "framework/material.h"

namespace GhostGame::Framework
{
    void CameraComponent::start(Framework::Engine& engine, Framework::Entity& entity)
    {
        pitch = engine.config.at("Camera").at("pitch").as_double();
        yaw = engine.config.at("Camera").at("yaw").as_double();
        roll = engine.config.at("Camera").at("roll").as_double();

        float fov = engine.config.at("Camera").at("fov").as_double();
        float aspectRatio = engine.config.at("Camera").at("aspectRatio").as_double();
        float nearClip = engine.config.at("Camera").at("nearClip").as_double();
        float farClip = engine.config.at("Camera").at("farClip").as_double();

        engine.viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        engine.projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    }

    void CameraComponent::update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime)
    {
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
        engine.viewMatrix = glm::mat4_cast(combinedRotation) * engine.viewMatrix;
    }

    void CameraComponent::draw(Framework::Engine& engine, Framework::Entity& entity, float deltaTime)
    {
    }
}