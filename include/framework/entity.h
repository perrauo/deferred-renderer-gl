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
        Entity();

        // Render the model
        void draw() const;

    private:
        std::unique_ptr<Model> _model;
    };
}