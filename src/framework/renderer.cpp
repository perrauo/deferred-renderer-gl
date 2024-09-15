#include "framework/renderer.h"
#include "framework/utils.h"
#include "framework/material.h"
#include "framework/engine.h"

#include <string>
#include <iostream>

namespace Experiment::Framework
{
    namespace GBuffer
    {
        // -------------------
        // GBufferResource
        // -------------------
        Resource::Resource(const glm::ivec2& dimensions)
        : dimensions(dimensions)
        {
            glGenFramebuffers(1, &frameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            // - position color buffer
            glGenTextures(1, &gPosition);
            glBindTexture(GL_TEXTURE_2D, gPosition);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
            // - normal color buffer
            glGenTextures(1, &gNormal);
            glBindTexture(GL_TEXTURE_2D, gNormal);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
            // - color + specular color buffer
            glGenTextures(1, &gAlbedo);
            glBindTexture(GL_TEXTURE_2D, gAlbedo);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions.x, dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);

            // - material ID buffer
            glGenTextures(1, &gMaterial);
            glBindTexture(GL_TEXTURE_2D, gMaterial);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, dimensions.x, dimensions.y, 0, GL_RED, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gMaterial, 0);

            // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
            glDrawBuffers(4, attachments);
            // - create and attach depth buffer (renderbuffer)
            glGenRenderbuffers(1, &rboDepth);
            glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, dimensions.x, dimensions.y);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
            // - finally check if framebuffer is complete
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Framebuffer not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        Resource::~Resource()
        {
            glDeleteTextures(1, &gPosition);
            glDeleteTextures(1, &gNormal);
            glDeleteTextures(1, &gAlbedo);
            glDeleteTextures(1, &gMaterial);
            glDeleteRenderbuffers(1, &rboDepth);
            glDeleteFramebuffers(1, &frameBuffer);
        }


        FrameBufferBinding::FrameBufferBinding(const Resource* resource)
        : _resource(resource)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, resource->frameBuffer);
        }

        FrameBufferBinding::~FrameBufferBinding()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        TextureBinding::TextureBinding(const Resource* resource)
        {
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gPosition);
            glBindTexture(GL_TEXTURE_2D, resource->gPosition);
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gNormal);
            glBindTexture(GL_TEXTURE_2D, resource->gNormal);
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gAlbedo);
            glBindTexture(GL_TEXTURE_2D, resource->gAlbedo);
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gMaterial);
            glBindTexture(GL_TEXTURE_2D, resource->gMaterial);
        }

        TextureBinding::~TextureBinding()
        {
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gPosition);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind gPosition
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gNormal);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind gNormal
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gAlbedo);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind gAlbedo
            glActiveTexture(GL_TEXTURE0 + (int)ReservedTextureSlot::gMaterial);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind gAlbedo
        }
    }

    // We are correctly drawing a quad filling the screen. This is fine
    void drawQuad()
    {
        static GLuint quadVAO = 0, quadVBO;
        if (!quadVAO)
        {
            // Vertex data for fullscreen quad
            GLfloat quadVertices[] = {
                // Positions   // TexCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                 1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                 1.0f, -1.0f,  1.0f, 0.0f,
                 1.0f,  1.0f,  1.0f, 1.0f
            };

            // Setup quad VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        }

        glBindVertexArray(quadVAO);
        glEnableVertexAttribArray(0); // aPos
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(0); // disable aPos
        glBindVertexArray(0);
    }
}