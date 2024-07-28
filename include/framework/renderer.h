#pragma once

#include "framework/api.h"
#include "framework/utils.h"

#include <memory>
#include <vector>
#include <string>

namespace GhostGame::Framework
{
    class Shader;
    class Material;

    namespace RenderPasses
    {

        namespace Geometry
        {
            constexpr char name[] = NAMEOF(Geometry);

            namespace Uniforms
            {
                constexpr char modelMatrix[] = "model";
                constexpr char viewMatrix[] = "view";
                constexpr char projectionMatrix[] = "projection";
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
        std::unique_ptr<RenderPass> geometryRenderPass;
        std::unique_ptr<RenderPass> lightingRenderPass;
        std::unique_ptr<RenderPass> postprocessRenderPass;

        Renderer() = default;

        ~Renderer() = default;

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        void render();

        
    };
}
