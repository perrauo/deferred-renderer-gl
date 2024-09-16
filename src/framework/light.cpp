#include "framework/light.h"
#include "framework/material.h"
#include "framework/engine.h"
#include "framework/entity.h"
#include "framework/renderer.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <boost/json.hpp>
#include <vector>

namespace Experiment::Framework
{
    void LightComponent::start(Engine& engine, Entity& entity)
    {
        auto pointLight = typeid(*this) == typeid(PointLightComponent) ? engine.config.at("PointLight").as_object() : engine.config.at("DirectionalLight").as_object();
        auto pointLightColor = pointLight.at("lightColor").as_object();
        color.r = pointLightColor.at("r").as_double();
        color.g = pointLightColor.at("g").as_double();
        color.b = pointLightColor.at("b").as_double();
        intensity = pointLight.at("lightIntensity").as_double();        
    }

    void LightComponent::update(Engine& engine, Entity& entity, float deltaTime)
    {
        // Update light position or direction if necessary
    }

    void PointLightComponent::drawLight(Engine& engine, Entity& entity, float deltaTime)
    {
        std::string lightPosUniform = "pointLights[" + std::to_string(componentId) + "].position";
        std::string lightColorUniform = "pointLights[" + std::to_string(componentId) + "].color";
        std::string lightIntensityUniform = "pointLights[" + std::to_string(componentId) + "].intensity";

        // Assuming you have a method to set uniforms in your shader
        engine.lightMaterial->setUniform(lightPosUniform, entity.transform.position);
        engine.lightMaterial->setUniform(lightColorUniform, color);
        engine.lightMaterial->setUniform(lightIntensityUniform, intensity);
    }

    void DirectionalLightComponent::drawLight(Engine& engine, Entity& entity, float deltaTime)
    {
        std::string lightDirUniform = "directionalLights[" + std::to_string(componentId) + "].direction";
        std::string lightColorUniform = "directionalLights[" + std::to_string(componentId) + "].color";
        std::string lightIntensityUniform = "directionalLights[" + std::to_string(componentId) + "].intensity";

        glm::vec3 transformedDirection = entity.transform.rotation * glm::vec3(0.0f, 0.0f, -1.0f);

        // Assuming you have a method to set uniforms in your shader
        engine.lightMaterial->setUniform(lightDirUniform, transformedDirection);
        engine.lightMaterial->setUniform(lightColorUniform, color);
        engine.lightMaterial->setUniform(lightIntensityUniform, intensity);
    }

    void DirectionalLightSystem::drawLight(Engine& engine, EntityCollection& entities, float deltaTime)
    {
        Super::drawLight(engine, entities, deltaTime);
        
        engine.lightMaterial->setUniform("numDirectionalLights", numComponents());
    }


    void PointLightSystem::drawLight(Engine& engine, EntityCollection& entities, float deltaTime)
    {
        Super::drawLight(engine, entities, deltaTime);

        engine.lightMaterial->setUniform("numPointLights", numComponents());
    }
}