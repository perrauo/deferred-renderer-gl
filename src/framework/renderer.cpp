#include "framework/renderer.h"
#include "framework/utils.h"
#include "framework/shader.h"

#include <string>

namespace GhostGame::Framework
{

    // -------------------
    // RenderPass
    // -------------------

    RenderPass::RenderPass(
    const std::string& vertexShaderPath
    , const std::string& fragmentShaderPath
    )
    : RenderPass(
    std::make_unique<Shader>(getPathToCurrent(vertexShaderPath))
    , std::make_unique<Shader>(getPathToCurrent(fragmentShaderPath))
    )
    {
    }

    RenderPass::RenderPass(
    std::unique_ptr<Shader>&& vertexShader
    , std::unique_ptr<Shader>&& fragmentShaer
    )
    : _vertexShader(std::move(vertexShader))
    , _fragmentShader(std::move(fragmentShaer))
    {
    }


    // -------------------
    // Renderer
    // -------------------

    void Renderer::render()
    {
    
    }
}