#pragma once

#include "framework/api.h"
#include "framework/utils.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <memory>
#include <vector>
#include <string>
#include <stack>

namespace GhostGame::Framework
{
    class Shader;
    class Material;
    class Engine;

    namespace DeferredShading
    {
        constexpr int numTexturesReserved = 4;

        namespace FinalPass
        {
            constexpr char name[] = NAMEOF(FinalPass);
        }

        namespace Uniforms
        {
            constexpr char screenTexture[] = "screenTexture";
            constexpr char gPosition[] = "gPosition";
            constexpr char gNormal[] = "gNormal";
            constexpr char gAlbedo[] = "gAlbedo";
        }
    }

    enum class ReservedTextureSlot : int
    {
        ScreenTexture, // Corresponds to GL_TEXTURE0..etc
        gPosition,
        gNormal,
        gAlbedo
    };

    class GHOSTGAME_FRAMEWORK_API GBuffer {
    
        bool _isBound = false;
        bool _areTexturesBound = false;
        bool _isInit = false;
    
    public:
        unsigned int frameBuffer = 0;
        unsigned int gPosition = 0, gNormal = 0, gAlbedo = 0;
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        unsigned int rboDepth = 0;

        int screenWidth = 0;
        int screenHeight = 0;
        
        GBuffer(int screenWidth, int screenHeight);
        ~GBuffer();
        GBuffer(GBuffer&&) = default;
        GBuffer(const GBuffer&) = delete;
        GBuffer& operator=(const GBuffer&) = delete;

        void bind();
        void unbind();
        void bindTextures();
        void unbindTextures();
        void init();
        void deinit();
        //void blitToDefaultFramebuffer();
        void drawQuad();
    };
        
    void drawQuad(Engine& engine);
}
