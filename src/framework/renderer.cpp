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
            unbindTextures();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

    void GBuffer::bindTextures()
    {
        if (!_areTexturesBound)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, gPosition);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, gNormal);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, gAlbedo);

            _areTexturesBound = true;
        }
    }

    void GBuffer::unbindTextures()
    {
        if (_areTexturesBound)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind gPosition
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind gNormal
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind gAlbedo

            _areTexturesBound = false;
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
            glGenTextures(1, &gAlbedo);
            glBindTexture(GL_TEXTURE_2D, gAlbedo);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
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
            glDeleteTextures(1, &gAlbedo);
            glDeleteRenderbuffers(1, &rboDepth);
            glDeleteFramebuffers(1, &gBuffer);

            _isInit = false;
        }
    }

    void GBuffer::blitToDefaultFramebuffer()
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        glBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0, screenWidth, screenHeight, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    }

    // We are correctly drawing a quad filling the screen. This is fine
    void GBuffer::drawQuad()
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