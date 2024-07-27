#include "framework/entity.h"

namespace GhostGame::Framework
{
    void Entity::draw(Engine& engine) const {
    }

    void Entity::update(Engine& engine, float deltaTime)
    {
        for (int i = components.size(); i >= 0; i--)
        {
            components[i]->update(engine, deltaTime);
        }
    }
}