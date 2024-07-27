#include "game/game.h"
#include "game/avatar.h"
#include "game/ghost.h"

#include "framework/engine.h"
#include "framework/model.h"
#include "framework/entity.h"

#include <filesystem>

namespace GhostGame
{
    void Game::start(Framework::Engine& engine)
    {
        using namespace Framework;

        for (const auto& entry : std::filesystem::directory_iterator("./sponza"))
        {
            auto model = std::make_unique<Model>(entry.path().string());
            auto entity = std::make_unique<Entity>(model);
            engine.add(std::move(entity));
        }

        engine.add(std::make_unique<Avatar>());
    }

    void Game::update(Framework::Engine& engine)
    {
    }

    void Game::render(Framework::Engine& engine)
    {
    }

    Game::~Game()
    {
    }
}