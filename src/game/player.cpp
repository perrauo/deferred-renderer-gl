#include "game/player.h"

#include "framework/entity.h"
#include "framework/engine.h"
#include "framework/camera.h"

namespace Experiment::Demo
{   
    using namespace Framework;

    // -------------------
    // PlayerBehavior
    // -------------------

    void PlayerComponent::start(Engine& engine, Entity& entity)
    {
    }

    void PlayerComponent::update(Engine& engine, Entity& entity, float deltaTime) {
        //         glfwGetCursorPos(window, &x, &y);
        glm::vec2 cursorPos = engine.getCursorPos();

        // Calculate the offset from the last frame
        double xOffset = cursorPos.x - lastCursorPos.x;
        double yOffset = cursorPos.y - lastCursorPos.y; // Fixed the reversal

        lastCursorPos = cursorPos;

        // Adjust the camera's rotation
        auto& camera = engine.getSimpleComponent<Framework::CameraComponent>(entity);
        camera.yaw -= xOffset; // Reversed the offset
        camera.pitch -= yOffset; // Reversed the offset

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (camera.pitch > 89.0f) camera.pitch = 89.0f;
        if (camera.pitch < -89.0f) camera.pitch = -89.0f;

        // Handle WASD input for player movement
        glm::vec3 direction(0.0f);
        if (engine.isKeyPressed(GLFW_KEY_W)) {
            direction += camera.getForward();
        }
        if (engine.isKeyPressed(GLFW_KEY_S)) {
            direction -= camera.getForward();
        }
        if (engine.isKeyPressed(GLFW_KEY_A)) {
            direction -= glm::normalize(glm::cross(camera.getForward(), camera.getUp()));
        }
        if (engine.isKeyPressed(GLFW_KEY_D)) {
            direction += glm::normalize(glm::cross(camera.getForward(), camera.getUp()));
        }

        // Normalize direction and apply movement
        if (glm::length(direction) > 0.0f) {
            direction = glm::normalize(direction);
            entity.transform.position += direction * movementSpeed * deltaTime;
        }
    }

    void PlayerComponent::draw(Engine& engine, Entity& entity, float deltaTime)
    { 
    }
}