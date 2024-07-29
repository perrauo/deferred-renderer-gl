#include <iostream>

#include "framework/engine.h"
#include "framework/material.h"

#include "game/game.h"

int main()
{
    using namespace GhostGame;
    using namespace GhostGame::Framework;
  

    // Create an instance of the Engine class    
    Engine engine;
    
    // Just opens the window
    engine.setup();

    auto renderer = std::make_unique<Renderer>();
    renderer->gbuffer = std::make_unique<GBuffer>(engine.screenWidth, engine.screenHeight);
    renderer->geometryRenderPass = std::make_unique<RenderPass>(RenderPasses::Geometry::name, RES("framework/shaders/geometry"));
    renderer->lightingRenderPass = std::make_unique<RenderPass>(RenderPasses::Lighting::name, RES("framework/shaders/lighting"));
    renderer->postprocessRenderPass = std::make_unique<RenderPass>(RenderPasses::Postprocess::name, RES("framework/shaders/postprocess"));
    engine.renderer = std::move(renderer);

    std::unique_ptr<Game> game = std::make_unique<Game>();
    engine.startGame(std::move(game));    

    engine.loop();

    return 0;
}
