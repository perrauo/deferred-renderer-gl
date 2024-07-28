#pragma once

#include "framework/api.h"

#include <memory>
#include <vector>
#include <string>

namespace GhostGame::Framework
{
    class Shader;

    class GHOSTGAME_FRAMEWORK_API RenderPass {

        std::unique_ptr<Shader> _vertexShader;

        std::unique_ptr<Shader> _fragmentShader;
        
    public:

        RenderPass() = default;

        ~RenderPass() = default;

        RenderPass(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        RenderPass(std::unique_ptr<Shader>&& vertexShader, std::unique_ptr<Shader>&& fragmentShader);

        RenderPass(const RenderPass&) = delete;
        RenderPass& operator=(const RenderPass&) = delete;
    };

    class GHOSTGAME_FRAMEWORK_API Renderer {

    public:
        std::vector<std::unique_ptr<RenderPass>> renderPasses;

        Renderer() = default;

        ~Renderer() = default;

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        void render();

        
    };
}
