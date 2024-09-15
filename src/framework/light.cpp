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
        if (type == LightType::Point) {
            auto pointLight = engine.config.at("PointLight").as_object();
            auto pointLightColor = pointLight.at("lightColor").as_object();
            color.r = pointLightColor.at("r").as_double();
            color.g = pointLightColor.at("g").as_double();
            color.b = pointLightColor.at("b").as_double();
            intensity = pointLight.at("lightIntensity").as_double();
        }
        else if (type == LightType::Directional) {
            auto directionalLight = engine.config.at("DirectionalLight").as_object();
            auto directionalLightColor = directionalLight.at("lightColor").as_object();
            color.r = directionalLightColor.at("r").as_double();
            color.g = directionalLightColor.at("g").as_double();
            color.b = directionalLightColor.at("b").as_double();
            intensity = directionalLight.at("lightIntensity").as_double();
            auto directionalLightDir = directionalLight.at("lightDir").as_object();
            direction.x = directionalLightDir.at("x").as_double();
            direction.y = directionalLightDir.at("y").as_double();
            direction.z = directionalLightDir.at("z").as_double();
        }
    }

    void LightComponent::update(Engine& engine, Entity& entity, float deltaTime)
    {
        // Update light position or direction if necessary
    }

    void LightComponent::drawLight(Engine& engine, Entity& entity, float deltaTime)
    {
        // Bind light data to shader
        auto& system = engine.getSystem<LightComponent>();
        if (type == LightType::Point) {
            std::string lightPosUniform = "pointLights[" + std::to_string(componentId) + "].position";
            std::string lightColorUniform = "pointLights[" + std::to_string(componentId) + "].color";
            std::string lightIntensityUniform = "pointLights[" + std::to_string(componentId) + "].intensity";

            // Assuming you have a method to set uniforms in your shader
            engine.lightMaterial->setUniform(lightPosUniform, entity.transform.position);
            engine.lightMaterial->setUniform(lightColorUniform, color);
            engine.lightMaterial->setUniform(lightIntensityUniform, intensity);
        }
        else if (type == LightType::Directional) {
            std::string lightDirUniform = "directionalLights[" + std::to_string(componentId) + "].direction";
            std::string lightColorUniform = "directionalLights[" + std::to_string(componentId) + "].color";
            std::string lightIntensityUniform = "directionalLights[" + std::to_string(componentId) + "].intensity";

            // Assuming you have a method to set uniforms in your shader
            engine.lightMaterial->setUniform(lightDirUniform, direction);
            engine.lightMaterial->setUniform(lightColorUniform, color);
            engine.lightMaterial->setUniform(lightIntensityUniform, intensity);
        }
    }
}