#include "framework/entity.h"

namespace GhostGame::Framework
{
    Entity::Entity(std::unique_ptr<Model>&& model)
    : model(std::move(model))
    {
    }

    void Entity::draw() const {
        
    }
}