#ifndef GHOSTGAME_ENTITY_H
#define GHOSTGAME_ENTITY_H

#include <GL/glew.h>
#include <vector>

#include "engine/types.h"

namespace GhostGame
{
    class Entity {
    public:
        // Constructor
        Entity();

        // Render the model
        void render() const;

    private:
    };
}

#endif