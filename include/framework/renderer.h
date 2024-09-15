#pragma once

#include "framework/api.h"
#include "framework/utils.h"
#include "framework/material.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/vec2.hpp>

#include <memory>
#include <vector>
#include <string>
#include <stack>

namespace Experiment::Framework
{
    class Shader;
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
            constexpr char gMaterial[] = "gMaterial";
        }
    }

    enum class ReservedTextureSlot : int
    {
        ScreenTexture, // Corresponds to GL_TEXTURE0..etc
        gPosition,
        gNormal,
        gAlbedo,
        gMaterial
    };

    namespace GBuffer
    {
        constexpr char name[] = NAMEOF(GBuffer);

        class EXPERIMENT_FRAMEWORK_API Resource {
        public:
            unsigned int frameBuffer = 0;
            unsigned int gPosition = 0, gNormal = 0, gAlbedo = 0, gMaterial = 0;
            unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            unsigned int rboDepth = 0;

            glm::ivec2 dimensions;
            std::unique_ptr<Material> material;

            Resource(std::unique_ptr<Material>&& material, const glm::ivec2& dimensions);
            ~Resource();
            Resource(Resource&&) = default;
            Resource(const Resource&) = delete;
            Resource& operator=(const Resource&) = delete;
        };

        class EXPERIMENT_FRAMEWORK_API FrameBufferBinding
        {
            const Resource* _resource = nullptr;
        public:
            FrameBufferBinding(const Resource* resource);
            ~FrameBufferBinding();
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
