#pragma once

#include "framework/math.h"

#include <vector>
#include <memory>
#include <unordered_map>

namespace GhostGame::Framework
{
    using EntityId = int;
    class Engine;

    class GHOSTGAME_FRAMEWORK_API Entity {
    public:
        
        EntityId id = -1;
        Transform transform;        

        bool markedForDeletion = false;
        bool hasStarted = false;

        Entity() = default;
        ~Entity() = default;

        Entity(const Entity&) = delete;
        Entity& operator=(const Entity&) = delete;

        operator bool() const {
            return id != -1;
        }
        operator EntityId() const {
            return id;
        }
    };

    class GHOSTGAME_FRAMEWORK_API Component {
    public:
        virtual void start(Engine& engine, Entity& entity) {}
        virtual void update(Engine& engine, Entity& entity, float deltaTime) {}
        virtual void draw(Engine& engine, Entity& entity, float deltaTime) {}
    };
    
    class ISystem 
    {
    public:
        virtual void start(Engine& engine, Entity& entity) = 0;
        virtual void update(Engine& engine, Entity& entity, float deltaTime) = 0;
        virtual void draw(Engine& engine, Entity& entity, float deltaTime) = 0;
    };

    template<typename T>
    class System : public ISystem 
    {    
        // TODO: We need to optimize with contiguous datatype
        // otherwise this defeats the point of ECS
        std::unordered_map<EntityId, T> _components;
    
    public:
        bool isValid = true;

        explicit operator bool() const {
            return isValid;
        }

        void start(Engine& engine, Entity& entity) override
        {
            auto it = _components.find(entity.id);
            if (it != _components.end())
            {
                it->second.start(engine, entity);
            }
        }

        void draw(Engine& engine, Entity& entity, float deltaTime) override
        {
            auto it = _components.find(entity.id);
            if (it != _components.end())
            {
                it->second.draw(engine, entity, deltaTime);
            }
        }

        void update(Engine& engine, Entity& entity, float deltaTime) override
        {
            auto it = _components.find(entity.id);
            if (it != _components.end())
            {                
                it->second.update(engine, entity, deltaTime);
            }
        }

        T& getComponent(EntityId id) {
            // operator[] on an unordered_map will create a new element if the key doesn't exist
            return _components[id];
        }

        T& addComponent(EntityId id) {
            // operator[] on an unordered_map will create a new element if the key doesn't exist
            return _components[id];
        }

        void removeComponent(EntityId id)
        {
            _components.erase(id);
        }
    };
}