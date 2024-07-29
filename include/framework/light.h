#pragma once

#include "framework/api.h"
#include "framework/utils.h"
#include "framework/entity.h"

#include <glm/glm.hpp> // For glm::vec3

namespace GhostGame::Framework
{
    namespace Lights
    {
        namespace PointLight
        {
            constexpr char name[] = NAMEOF(PointLight);

            namespace Uniforms
            {
                constexpr char model[] = "model";
                constexpr char view[] = "view";
                constexpr char projection[] = "projection";
                constexpr char lightPos[] = "lightPos";
                constexpr char lightColor[] = "lightColor";
                constexpr char lightIntensity[] = "intensity";
            }

            namespace Out
            {
                constexpr char FragColor[] = "FragColor ";
            }
        }
    }

    class Engine;
    class Material;
    class MaterialInstance;

    class GHOSTGAME_FRAMEWORK_API PointLightComponent : public Component {
    public:
        glm::vec3 color;
        float intensity;
        std::shared_ptr<MaterialInstance> lightMaterial;

        virtual void start(Engine& engine, Entity& entity);
        virtual void update(Engine& engine, Entity& entity, float deltaTime);
        virtual void drawLight(Engine& engine, Entity& entity, float deltaTime);
        virtual void endDrawLight(Engine& engine, Entity& entity, float deltaTime);

    private:
        virtual void doDrawLight(Engine& engine, Entity& entity, float deltaTime);
    };
}
