#include "game/game.h"
#include "game/types.h"

#include "framework/engine.h"
#include "framework/model.h"
#include "framework/entity.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <iterator>
#include <boost/json.hpp>

namespace GhostGame
{
    void Game::start(Framework::Engine& engine)
    {
        using namespace Framework;

        std::ifstream file("./game_config.json");
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        auto config = boost::json::parse(content);
        auto someValue = config.at("enemySpawnFrequency").as_string();

        for (const auto& entry : std::filesystem::directory_iterator("./environment"))
        {
            auto model = std::make_unique<Model>(entry.path().string());
            auto [id, entity] = engine.spawnEntity();
            entity.components.push_back(std::make_unique< ModelRenderer>(std::move(model)));
        }

        auto [id, player] = engine.spawnEntity();
        playerId = id;
        player.components.push_back(std::make_unique<PlayerBehavior>());
    }

    void Game::update(Framework::Engine& engine, float deltaTime)
    {
        static auto lastSpawnTime = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastSpawnTime);

        auto ghost = std::make_unique<Ghost>();
        ghost->transform.position = player->transform.position; // Assuming Avatar has a getPosition method
        engine.add(std::move(ghost));
    }

    void Game::render(Framework::Engine& engine)
    {
    }

    Game::~Game()
    {
    }
}