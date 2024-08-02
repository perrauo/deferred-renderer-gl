#include "framework/light.h"
#include "framework/material.h"
#include "framework/engine.h"
#include "framework/entity.h"
#include "framework/renderer.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <boost/json.hpp>

namespace GhostGame::Framework
{
    void PointLightComponent::start(Engine& engine, Entity& entity)
    {
        auto pointLight = engine.config.at("PointLight").as_object();
        auto pointLightColor = pointLight.at("lightColor").as_object();
        color.r = pointLightColor.at("r").as_double();
        color.g = pointLightColor.at("g").as_double();
        color.b = pointLightColor.at("b").as_double();
        intensity = pointLight.at("lightIntensity").as_double();
        lightMaterial = std::make_shared<MaterialInstance>(engine.pointLightMaterial);
    }
    
    void PointLightComponent::update(Engine& engine, Entity& entity, float deltaTime)
    {
    }
    
    void PointLightComponent::drawLight(Engine& engine, Entity& entity, float deltaTime)
    {
        using namespace Lights;

        lightMaterial->setUniform(Uniforms::model, entity.transform.getMatrix());
        lightMaterial->setUniform(Uniforms::view, engine.viewMatrix);
        lightMaterial->setUniform(Uniforms::projection, engine.projectionMatrix);

        lightMaterial->setUniform(Materials::Uniforms::screenSize, engine.screenSize);
        lightMaterial->setUniform(Lights::Uniforms::lightColor, color);
        lightMaterial->setUniform(Lights::Uniforms::lightIntensity, intensity);
        lightMaterial->setUniform(Lights::Uniforms::lightPos, entity.transform.getMatrix());
        lightMaterial->setUniform(Uniforms::model, entity.transform.getMatrix());

        lightMaterial->bind(engine);
        
        doDrawLight(engine, entity, deltaTime);

        lightMaterial->unbind(engine);
    }

    void PointLightComponent::endDrawLight(Engine& engine, Entity& entity, float deltaTime)
    {
    }

    void PointLightComponent::doDrawLight(Engine& engine, Entity& entity, float deltaTime)
    {
        // 1. Create a dummy VAO and VBO:
        static GLuint dummyVAO = 0, dummyVBO = 0;
        if (!dummyVAO)
        {
            glGenVertexArrays(1, &dummyVAO);
            glGenBuffers(1, &dummyVBO);
            // 2. Bind the dummy VAO and VBO:
            glBindVertexArray(dummyVAO);
            glBindBuffer(GL_ARRAY_BUFFER, dummyVBO);
            // 3. Define a single vertex with a position of(0, 0, 0) :
            GLfloat vertex[] = { 0.0f, 0.0f, 0.0f };
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
            // 4. Set up the vertex attribute :
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
        }
        // 5. Draw the single vertex :
        glDrawArrays(GL_POINTS, 0, 1);
    }
}
