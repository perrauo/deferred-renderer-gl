#include "game/game.h"
#include "game/types.h"

#include "framework/engine.h"
#include "framework/mesh.h"
#include "framework/entity.h"
#include "framework/utils.h"

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

        std::filesystem::path currentPath = std::filesystem::current_path();
        std::ifstream file(getPathToCurrent("resources/game/config.json"));
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        auto config = boost::json::parse(content);
        _enemySpawnFrequency = config.at("enemySpawnFrequency").as_double();

        engine.addSystem<PlayerComponent>();
        engine.addSystem<CameraComponent>();
        auto& meshSystem = engine.addSystem<MeshComponent>();
        engine.addSystem<EnemyComponent>();

        for (const auto& entry : std::filesystem::directory_iterator(getPathToCurrent("resources/game/environment")))
        {
            if (entry.path().extension() == ".dae") {
                auto& entity = engine.spawnEntity();                
                auto& meshComp = meshSystem.addComponent(entity.id);
                meshComp.mesh = std::make_unique<Mesh>(entry.path().string());
            }
        }

        for (const auto& entry : std::filesystem::directory_iterator(getPathToCurrent("resources/game/entities/enemy")))
        {
            if (entry.path().extension() == ".dae") {
                _enemyMesh = std::make_shared<Mesh>(entry.path().string());
                break;
            }
        }

        _playerId = engine.spawnEntity().id;
    }

    void Game::update(Framework::Engine& engine, float deltaTime)
    {
        using namespace Framework;

        auto& enemySystem = engine.getSystem<EnemyComponent>();
        auto& meshSystem = engine.getSystem<MeshComponent>();

        static auto lastSpawnTime = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastSpawnTime);

        if (duration.count() >= _enemySpawnFrequency) 
        {
            auto& player = engine.getEntity(_playerId);
            auto& entity = engine.spawnEntity();
            entity.transform.position = player.transform.position;
            enemySystem.addComponent(entity.id);
            auto& meshComp = meshSystem.addComponent(entity.id);
            meshComp.mesh = _enemyMesh;

            lastSpawnTime = now;
        }

        // Update player components
        if (auto& entity = engine.getEntity(_playerId))
        {
            player.update(engine, entity, deltaTime);
            camera.update(engine, entity, deltaTime);
        }
    }

    void Game::render(Framework::Engine& engine)
    {
    }
}