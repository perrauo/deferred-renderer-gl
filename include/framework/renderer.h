#pragma once

#include "framework/api.h"
#include "framework/utils.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <memory>
#include <vector>
#include <string>
#include <stack>

namespace Experiment::Framework
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

    namespace GBuffer
    {
        constexpr char name[] = NAMEOF(GBuffer);

        class EXPERIMENT_FRAMEWORK_API Resource {
        public:
            unsigned int frameBuffer = 0;
            unsigned int gPosition = 0, gNormal = 0, gAlbedo = 0;
            unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
            unsigned int rboDepth = 0;

            glm::ivec2 dimensions;
            std::unique_ptr<Material> material;

            Resource(std::unique_ptr<Material>&& material, const glm::ivec2& dimensions);
            ~Resource();
            Resource(Resource&&) = default;
            Resource(const Resource&) = delete;
            Resource& operator=(const Resource&) = delete;
        };

        class EXPERIMENT_FRAMEWORK_API FramebufferBinding
        {
            const Resource* _resource = nullptr;
        public:
            FramebufferBinding(const Resource* resource);
            ~FramebufferBinding();
        };

        class EXPERIMENT_FRAMEWORK_API TextureBinding
        {
            const Resource* _resource = nullptr;
        public:
            TextureBinding(const Resource* resource);
            ~TextureBinding();
        };
    }

    void drawQuad();
}
