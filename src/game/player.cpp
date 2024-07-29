#include "game/player.h"

#include "framework/entity.h"
#include "framework/engine.h"
#include "framework/camera.h"

namespace GhostGame
{
    // -------------------
    // PlayerBehavior
    // -------------------

    void PlayerComponent::start(Framework::Engine& engine, Framework::Entity& entity)
    {
    }

    void PlayerComponent::update(Framework::Engine& engine, Framework::Entity& entity, float deltaTime) {
        glm::vec2 cursorPos = engine.getCursorPos();

        // Calculate the offset from the last frame
        double xOffset = cursorPos.x - lastCursorPos.x;
        double yOffset = cursorPos.y - lastCursorPos.y; // Fixed the reversal

        lastCursorPos = cursorPos;

        // Adjust the camera's rotation
        auto& camera = engine.getComponent<Framework::CameraComponent>(entity);
        camera.yaw -= xOffset; // Reversed the offset
        camera.pitch -= yOffset; // Reversed the offset

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (camera.pitch > 89.0f) camera.pitch = 89.0f;
        if (camera.pitch < -89.0f) camera.pitch = -89.0f;
    }

    void PlayerComponent::draw(Framework::Engine& engine, Framework::Entity& entity, float deltaTime)
    { 
    }
}