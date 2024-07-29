#pragma once

#include "framework/api.h"
#include "framework/entity.h"
#include "framework/renderer.h"
#include "framework/material.h"
#include "framework/game.h"
#include "framework/math.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include <memory>
#include <unordered_map>
#include <vector>
#include <utility> // pair
#include <functional> // reference_wrapper
// The cost of using typeid is relatively low compared to dynamic_cast. It involves only one comparison of std::type_info.
// TODO: we can easily switch with an enum later on
#include <typeindex>
#include <typeinfo>

namespace GhostGame::Framework
{
    using EntityId = int;

    class GHOSTGAME_FRAMEWORK_API Engine {
    private:
        std::unordered_map<EntityId, Entity> _entities;
        std::unordered_map<std::type_index, std::unique_ptr<ISystem>> _systems;

        float _lastTime = 0;

        EntityId _nextEntityId = 0;

        void update();

    public:

        GLFWwindow* window = nullptr;
        int screenHeight = 0;
        int screenWidth = 0;

        glm::mat4 viewMatrix = Math::Identity4x4;
        glm::mat4 projectionMatrix = Math::Identity4x4;

        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<IGame> game;
        std::unique_ptr<Material> pointLightMaterial;

        Engine();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        int setup();

        void loop();

        // TODO: remove level of indirection. renderer should not call upon engine.drawEntities
        // Maybe use a lambda?
        void drawEntities(float deltaTime);

        void drawLights(float deltaTime);

        void startGame(std::unique_ptr<IGame>&& game); 

        void stop();

        glm::vec2 getCursorPos() const;

        template<typename T>
        System<T>& addSystem()
        {
            auto typeIndex = std::type_index(typeid(T));
            auto system = std::make_unique<System<T>>();
            auto& ref = *system;
            _systems[typeIndex] = std::move(system);
            return ref;
        }

        template<typename T>
        System<T>& getSystem() {
            auto typeIndex = std::type_index(typeid(T));
            auto it = _systems.find(typeIndex);
            if (it != _systems.end()) {
                return *static_cast<System<T>*>(it->second.get());
            }
            System<T> sInvalidSystem;
            sInvalidSystem.isValid = false;
            return sInvalidSystem;
        }

        template<typename T>
        T& getComponent(EntityId id)
        {
            return getSystem<T>().getComponent(id);
        }

        Entity& spawnEntity();

        void despawnEntity(EntityId id);

        Entity& getEntity(EntityId id);
    };
}
