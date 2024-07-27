#pragma once

#include "framework/types.h"
#include "framework/component.h"
#include "framework/mesh.h"

#include <GL/glew.h>
#include <vector>
#include <memory>

namespace GhostGame::Framework
{
    using EntityId = int;

    class GHOSTGAME_FRAMEWORK_API Entity {
    public:
        
        Transform transform;

        std::vector<std::unique_ptr<Component>> components;

        bool markedForDeletion = false;

        Entity() = default;
        ~Entity() = default;

        Entity(const Entity&) = delete;
        Entity& operator=(const Entity&) = delete;
       
        void draw(Engine& engine) const;
        
        void update(Engine& engine, float deltaTime);
    };
}