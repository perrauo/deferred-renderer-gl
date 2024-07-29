#include "framework/renderer.h"
#include "framework/utils.h"
#include "framework/material.h"
#include "framework/engine.h"

#include <string>
#include <iostream>

namespace GhostGame::Framework
{
    // -------------------
    // GBuffer
    // -------------------
    GBuffer::GBuffer(int screenWidth, int screenHeight)
    : screenWidth(screenWidth)
    , screenHeight(screenHeight)
    {
    }

    GBuffer::~GBuffer()
    {
        unbind();
        deinit();
    }

    void GBuffer::unbind()
    {
        if (_isBound)
        {
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
            _isBound = false;
        }
    }

    void GBuffer::bind()
    {
        if (!_isBound)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

            _isBound = true;
        }
    }

    void GBuffer::init()
    {
        if (!_isInit)
        {
            glGenFramebuffers(1, &gBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
            // - position color buffer
            glGenTextures(1, &gPosition);
            glBindTexture(GL_TEXTURE_2D, gPosition);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, screenWidth, screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
            // - normal color buffer
            glGenTextures(1, &gNormal);
            glBindTexture(GL_TEXTURE_2D, gNormal);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, screenWidth, screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
            // - color + specular color buffer
            glGenTextures(1, &gAlbedoSpec);
            glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
            // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
            glDrawBuffers(3, attachments);
            // - create and attach depth buffer (renderbuffer)
            glGenRenderbuffers(1, &rboDepth);
            glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
            // - finally check if framebuffer is complete
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            _isInit = true;
        }
    }

    void GBuffer::deinit()
    {
        if (_isInit)
        {
            glDeleteTextures(1, &gPosition);
            glDeleteTextures(1, &gNormal);
            glDeleteTextures(1, &gAlbedoSpec);
            glDeleteRenderbuffers(1, &rboDepth);
            glDeleteFramebuffers(1, &gBuffer);

            _isInit = false;
        }
    }

    // -------------------
    // RenderPass
    // -------------------

    RenderPass::RenderPass(
    const std::string& name
    , const std::string& materialPath
    )
    : RenderPass(std::make_shared<Material>(name, materialPath)
    )
    {
    }

    RenderPass::RenderPass(const std::shared_ptr<Material>& material)
    : material(material)
    {
    }


    // -------------------
    // Renderer
    // -------------------

    void Renderer::drawQuad(Engine& engine)
    {
        static unsigned int quadVAO = 0;
        static unsigned int quadVBO;
        if (quadVAO == 0)
        {
            float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // setup plane VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        }
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

    void Renderer::init(Engine& engine)
    {
        gbuffer->init();
    }

    void Renderer::render(Engine& engine, float deltaTime)
    {
        using namespace RenderPasses;

        gbuffer->bind();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        geometryRenderPass->material->use();
        geometryRenderPass->material->setUniform(Geometry::Uniforms::view, engine.viewMatrix);
        geometryRenderPass->material->setUniform(Geometry::Uniforms::projection, engine.projectionMatrix);
        engine.drawEntities(deltaTime);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. Lighting pass: use the gbuffer to calculate the scene's lighting
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lightingRenderPass->material->use();

        // Bind GBuffer textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gbuffer->gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gbuffer->gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gbuffer->gAlbedoSpec);

        engine.drawLights(deltaTime);

        // Draw a quad that covers the whole screen
        drawQuad(engine);

        // 3. Copy the depth buffer to the default framebuffer's depth buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gbuffer->gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        glBlitFramebuffer(0, 0, engine.screenWidth, engine.screenHeight, 0, 0, engine.screenWidth, engine.screenHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

        gbuffer->unbind();

        // 4. Post-processing pass
        // TODO postprocessRenderPass->material->use();
        // drawQuad(engine);
    }

}