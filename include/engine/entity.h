#ifndef GHOSTGAME_ENTITY_H
#define GHOSTGAME_ENTITY_H

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "engine/types.h"

namespace GhostGame
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

#endif