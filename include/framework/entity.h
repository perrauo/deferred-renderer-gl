#pragma once

#include "framework/types.h"
#include "framework/component.h"
#include "framework/model.h"

#include <GL/glew.h>
#include <vector>
#include <memory>

namespace GhostGame::Framework
{
    using EntityId = int;

    class Entity {
    public:
        
        Transform transform;

        std::unique_ptr<Model> model;

        std::vector<std::unique_ptr<Component>> components;

        bool markedForDeletion = false;

        Entity(std::unique_ptr<Model>&& model);
       
        void draw() const;
        
        void update(float deltaTime);
    };
}