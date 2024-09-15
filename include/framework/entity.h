#pragma once

#include "framework/math.h"

#include <vector>
#include <memory>
#include <unordered_map>

namespace Experiment::Framework
{
    using EntityId = int;
    class Engine;

    class EXPERIMENT_FRAMEWORK_API Entity {
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

    class EXPERIMENT_FRAMEWORK_API Component {
    public:
        int componentId = -1; // Add componentId to the Component class

        virtual void start(Engine& engine, Entity& entity) {}
        virtual void update(Engine& engine, Entity& entity, float deltaTime) {}
        virtual void draw(Engine& engine, Entity& entity, float deltaTime) {}
        virtual void endDraw(Engine& engine, Entity& entity, float deltaTime) {}
        virtual void drawLight(Engine& engine, Entity& entity, float deltaTime) {}
        virtual void endDrawLight(Engine& engine, Entity& entity, float deltaTime) {}
    };

    class ISystem
    {
    public:
        virtual void start(Engine& engine, Entity& entity) = 0;
        virtual void update(Engine& engine, Entity& entity, float deltaTime) = 0;
        virtual void draw(Engine& engine, Entity& entity, float deltaTime) = 0;
        virtual void endDraw(Engine& engine, Entity& entity, float deltaTime) = 0;
        virtual void drawLight(Engine& engine, Entity& entity, float deltaTime) = 0;
        virtual void endDrawLight(Engine& engine, Entity& entity, float deltaTime) = 0;
    };

    template<typename T>
    class System : public ISystem
    {
        std::vector<T> _components;
        std::unordered_map<EntityId, int> _componentIndices;

    public:
        bool isValid = true;

        explicit operator bool() const {
            return isValid;
        }

        void start(Engine& engine, Entity& entity) override
        {
            auto it = _componentIndices.find(entity.id);
            if (it != _componentIndices.end())
            {
                _components[it->second].start(engine, entity);
            }
        }

        void draw(Engine& engine, Entity& entity, float deltaTime) override
        {
            auto it = _componentIndices.find(entity.id);
            if (it != _componentIndices.end())
            {
                _components[it->second].draw(engine, entity, deltaTime);
            }
        }

        void endDraw(Engine& engine, Entity& entity, float deltaTime) override
        {
            auto it = _componentIndices.find(entity.id);
            if (it != _componentIndices.end())
            {
                _components[it->second].endDraw(engine, entity, deltaTime);
            }
        }

        void drawLight(Engine& engine, Entity& entity, float deltaTime) override
        {
            auto it = _componentIndices.find(entity.id);
            if (it != _componentIndices.end())
            {
                _components[it->second].drawLight(engine, entity, deltaTime);
            }
        }

        void endDrawLight(Engine& engine, Entity& entity, float deltaTime) override
        {
            auto it = _componentIndices.find(entity.id);
            if (it != _componentIndices.end())
            {
                _components[it->second].endDrawLight(engine, entity, deltaTime);
            }
        }

        void update(Engine& engine, Entity& entity, float deltaTime) override
        {
            auto it = _componentIndices.find(entity.id);
            if (it != _componentIndices.end())
            {
                _components[it->second].update(engine, entity, deltaTime);
            }
        }

        T& getComponent(EntityId id) {
            auto it = _componentIndices.find(id);
            if (it != _componentIndices.end()) {
                return _components[it->second];
            }
            throw std::runtime_error("Component not found");
        }

        T& addComponent(EntityId id) {
            int index = _components.size();
            _components.push_back(T());
            _components.back().componentId = index;
            _componentIndices[id] = index;
            return _components.back();
        }

        void removeComponent(EntityId id)
        {
            auto it = _componentIndices.find(id);
            if (it != _componentIndices.end()) {
                int index = it->second;
                _components.erase(_components.begin() + index);
                _componentIndices.erase(it);

                // Update indices of remaining components
                for (auto& pair : _componentIndices) {
                    if (pair.second > index) {
                        pair.second--;
                        _components[pair.second].componentId = pair.second;
                    }
                }
            }
        }
    };
}
