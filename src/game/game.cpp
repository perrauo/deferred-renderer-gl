#include "game/game.h"
#include "game/types.h"

#include "framework/engine.h"
#include "framework/mesh.h"
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
        enemySpawnFrequency = config.at("enemySpawnFrequency").as_double();

        for (const auto& entry : std::filesystem::directory_iterator("./environment"))
        {
            if (entry.path().extension() == ".dae") {
                auto mesh = std::make_unique<Mesh>(entry.path().string());
                auto [id, entity] = engine.spawnEntity();
                entity.components.push_back(std::make_unique<MeshRenderer>(std::move(mesh)));
            }
        }

        for (const auto& entry : std::filesystem::directory_iterator("./entities/enemy"))
        {
            if (entry.path().extension() == ".dae") {
                enemyModel = std::make_shared<Mesh>(entry.path().string());
                break;
            }
        }

        auto [id, player] = engine.spawnEntity();
        playerId = id;
        player.components.push_back(std::make_unique<PlayerBehavior>());
    }

    void Game::update(Framework::Engine& engine, float deltaTime)
    {
        using namespace Framework;

        static auto lastSpawnTime = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastSpawnTime);

        if (duration.count() >= enemySpawnFrequency) 
        {
            for (const auto& entry : std::filesystem::directory_iterator("./entities/enemy"))
            {
                auto& player = engine.getEntity(playerId);
                auto [id, enemy] = engine.spawnEntity();
                enemy.transform.position = player.transform.position;
                enemy.components.push_back(std::make_unique<MeshRenderer>(enemyModel));
                lastSpawnTime = now;
            }
        }
    }

    void Game::render(Framework::Engine& engine)
    {
    }
}