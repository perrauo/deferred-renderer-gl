#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "framework/types.h"
#include "framework/model.h"

namespace GhostGame::Framework
{
    class Entity {
    public:
        // Constructor
        Entity(std::unique_ptr<Model>&& model);

        // Render the model
        void draw() const;
        
        Transform transform;

        std::unique_ptr<Model> model;
    };
}