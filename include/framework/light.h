#pragma once

#include "framework/api.h"
#include "framework/utils.h"
#include "framework/entity.h"

#include <glm/glm.hpp> // For glm::vec3

namespace Experiment::Framework
{
    namespace Lights
    {
        namespace Uniforms
        {
            constexpr char model[] = "model";
            constexpr char view[] = "view";
            constexpr char projection[] = "projection";
            constexpr char lightPos[] = "lightPos";
            constexpr char lightColor[] = "lightColor";
            constexpr char lightIntensity[] = "lightIntensity";
        }

        namespace PointLight
        {
            constexpr char name[] = NAMEOF(PointLight);
        }

        namespace Light
        {
            constexpr char name[] = NAMEOF(Light);
        }
    }

    class Engine;
    class Material;
    class MaterialInstance;

    enum class LightType : int
    {
        Invalid = -1,
        Point,
        Directional
    };

    class EXPERIMENT_FRAMEWORK_API LightComponent : public Component {
    public:
        glm::vec3 color;
        float intensity;
        LightType type = LightType::Invalid;
        glm::vec3 direction;

        virtual void start(Engine& engine, Entity& entity);
        virtual void update(Engine& engine, Entity& entity, float deltaTime);
        virtual void drawLight(Engine& engine, Entity& entity, float deltaTime);
        virtual void endDrawLight(Engine& engine, Entity& entity, float deltaTime);

    private:
        virtual void doDrawLight(Engine& engine, Entity& entity, float deltaTime);
    };
}
