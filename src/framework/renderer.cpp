#include "framework/renderer.h"
#include "framework/utils.h"
#include "framework/material.h"

#include <string>

namespace GhostGame::Framework
{

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

    void Renderer::render()
    {
        // TODO
    }
}