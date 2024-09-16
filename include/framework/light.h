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

        virtual void start(Engine& engine, Entity& entity);
        virtual void update(Engine& engine, Entity& entity, float deltaTime);
        virtual void drawLight(Engine& engine, Entity& entity, float deltaTime) {}
    };


    class EXPERIMENT_FRAMEWORK_API PointLightComponent : public LightComponent {
    public:
        virtual void drawLight(Engine& engine, Entity& entity, float deltaTime) override;
    };

    class EXPERIMENT_FRAMEWORK_API PointLightSystem : public System<PointLightComponent>
    {
        using Super = System<PointLightComponent>;
    public:
        void drawLight(Engine& engine, EntityCollection& entities, float deltaTime) override;
    };

    class EXPERIMENT_FRAMEWORK_API DirectionalLightComponent : public LightComponent {
    public:
        virtual void drawLight(Engine& engine, Entity& entity, float deltaTime) override;
    };

    class EXPERIMENT_FRAMEWORK_API DirectionalLightSystem : public System<DirectionalLightComponent>
    {
        using Super = System<DirectionalLightComponent>;
    public:
        void drawLight(Engine& engine, EntityCollection& entities, float deltaTime) override;
    };
       
}
