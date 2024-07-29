#include "framework/light.h"
#include "framework/material.h"
#include "framework/engine.h"
#include "framework/entity.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <boost/json.hpp>

namespace GhostGame::Framework
{
    void PointLightComponent::start(Engine& engine, Entity& entity)
    {
        std::ifstream configFile("config.json");
        boost::json::value configJson = boost::json::parse(configFile);
        auto pointLight = configJson.at("PointLight").as_object();
        auto pointLightColor = pointLight.at("color").as_object();
        color.r = pointLightColor.at("r").as_int64();
        color.g = pointLightColor.at("g").as_int64();
        color.b = pointLightColor.at("b").as_int64();
        intensity = pointLight.at("intensity").as_double();
        material = std::make_shared<MaterialInstance>(engine.pointLightMaterial);
    }
    
    void PointLightComponent::update(Engine& engine, Entity& entity, float deltaTime)
    {
    }
    
    void PointLightComponent::draw(Engine& engine, Entity& entity, float deltaTime)
    {
        using namespace Lights::PointLight;
        material->use();  // Use the light's shader
        material->setUniform(Uniforms::lightColor, color);
        material->setUniform(Uniforms::lightIntensity, intensity);
        material->setUniform(Uniforms::model, entity.transform.getMatrix());
        material->setUniform(Uniforms::lightPos, entity.transform.getMatrix());
    }
}
