#pragma once

#include "framework/api.h"
#include "framework/utils.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <memory>
#include <vector>
#include <string>

namespace GhostGame::Framework
{
    class Shader;
    class Material;
    class Engine;

    namespace RenderPasses
    {

        namespace Geometry
        {
            constexpr char name[] = NAMEOF(Geometry);

            namespace Uniforms
            {
                constexpr char model[] = "model";
                constexpr char view[] = "view";
                constexpr char projection[] = "projection";
                constexpr char texture_diffuse1[] = "texture_diffuse1";
                constexpr char texture_specular1[] = "texture_specular1";
            }

            namespace Attributes
            {
                constexpr char aPos[] = "aPos";
                constexpr char aNormal[] = "aNormal";
                constexpr char aTexCoords[] = "aTexCoords";
            }

            namespace Out
            {
                constexpr char gPosition[] = "gPosition";
                constexpr char gNormal[] = "gNormal";
                constexpr char gAlbedoSpec[] = "gAlbedoSpec";
            }
        }


        namespace Lighting
        {
            constexpr char name[] = NAMEOF(Lighting);

            namespace Uniforms
            {
                constexpr char gPosition[] = "gPosition";
                constexpr char gNormal[] = "gNormal";
                constexpr char gAlbedoSpec[] = "gAlbedoSpec";
                constexpr char lightPos[] = "lightPos";
                constexpr char viewPos[] = "viewPos";
                constexpr char lightColor[] = "lightColor";
            }
        }

        namespace Postprocess
        {
            constexpr char name[] = NAMEOF(Postprocess);

            namespace Uniforms
            {
                constexpr char screenTexture[] = "screenTexture";
            }
        }

        namespace Transparent
        {
            constexpr char name[] = NAMEOF(Transparent);
        }
    }

    class GHOSTGAME_FRAMEWORK_API GBuffer {
    
        bool _isBound = false;
        bool _isInit = false;
    
    public:
        unsigned int gBuffer = 0;
        unsigned int gPosition = 0, gNormal = 0, gAlbedoSpec = 0;
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        unsigned int rboDepth = 0;

        int screenWidth = 0;
        int screenHeight = 0;
        
        GBuffer(int screenWidth, int screenHight);
        ~GBuffer();
        GBuffer(GBuffer&&) = default;
        GBuffer(const GBuffer&) = delete;
        GBuffer& operator=(const GBuffer&) = delete;

        void bind();
        void unbind();
        void init();
        void deinit();
    };


    class GHOSTGAME_FRAMEWORK_API RenderPass {        
    public:
        std::shared_ptr<Material> material;

        RenderPass() = default;

        ~RenderPass() = default;

        RenderPass(
        const std::string& name
        , const std::string& materialPath
        );

        RenderPass(const std::shared_ptr<Material>& material);

        RenderPass(const RenderPass&) = delete;
        RenderPass& operator=(const RenderPass&) = delete;
    };

    class GHOSTGAME_FRAMEWORK_API Renderer {

    public:        
        std::unique_ptr<GBuffer> gbuffer;
        std::unique_ptr<RenderPass> geometryRenderPass;
        std::unique_ptr<RenderPass> lightingRenderPass;
        std::unique_ptr<RenderPass> postprocessRenderPass;

        Renderer() = default;

        ~Renderer() = default;

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        void render(Engine& engine, float deltaTime);
        void init(Engine& engine);
    
    private:
        
        void drawQuad(Engine& engine);
    };
}
