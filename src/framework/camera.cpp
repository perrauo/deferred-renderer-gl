#include "framework/camera.h"
#include "framework/engine.h"
#include "framework/renderer.h"
#include "framework/material.h"
#include "framework/preprocessor.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>  // for glm::rotate
#include <glm/gtc/quaternion.hpp>  // for glm::quat
#include <glm/gtx/quaternion.hpp>  // for glm::rotate (quaternion)

namespace Experiment::Framework
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

        // Calculate the initial forward vector
        glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
        // Use the forward vector to calculate the initial view matrix
        engine.viewMatrix = glm::lookAt(entity.transform.position, forward, glm::vec3(0.0f, 1.0f, 0.0f));
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

        // Calculate the camera's new forward, up and right vectors
        glm::vec3 forward = glm::normalize(glm::rotate(combinedRotation, glm::vec3(0.0f, 0.0f, -1.0f)));
        glm::vec3 up = glm::normalize(glm::rotate(combinedRotation, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 right = glm::cross(forward, up);

        // Calculate the camera's position
        glm::vec3& position = entity.transform.position;

        // Calculate the view matrix from the camera's position and orientation
        engine.viewMatrix = glm::lookAt(position, position + forward, up);
    }

    glm::vec3 CameraComponent::getUp() const
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

        // Calculate and return the up vector
        return glm::normalize(glm::rotate(combinedRotation, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    glm::vec3 CameraComponent::getForward() const
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

        // Calculate and return the forward vector
        return glm::normalize(glm::rotate(combinedRotation, glm::vec3(0.0f, 0.0f, -1.0f)));
    }

    void CameraComponent::draw(Framework::Engine& engine, Framework::Entity& entity, float deltaTime)
    {
    }
}