#include "game/game.h"
#include "game/types.h"

#include "framework/engine.h"
#include "framework/model.h"
#include "framework/mesh.h"
#include "framework/material.h"
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

        std::ifstream file(RES("game/config.json"));
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        auto config = boost::json::parse(content);
        _enemySpawnFrequency = config.at("enemySpawnFrequency").as_double();

        _playerId = engine.spawnEntity();
        auto& playerSystem = engine.addSystem<PlayerComponent>();
        auto& cameraSystem = engine.addSystem<CameraComponent>();
        playerSystem.addComponent(_playerId);
        cameraSystem.addComponent(_playerId);
        
        auto& meshSystem = engine.addSystem<MeshComponent>();
        engine.addSystem<EnemyComponent>();       

        for (const auto& entry : std::filesystem::directory_iterator(RES("game/environment")))
        {
            if (entry.path().extension() == ".dae") {
                ModelLoadContext loadContext;
                loadContext.baseTexturePath = "game/environment";
                loadContext.baseMaterial = engine.lambertMaterial;
                loadModel(entry.path().string(), loadContext);
                for (auto& [_, loadedMesh] : loadContext.meshes)
                {
                    auto& entity = engine.spawnEntity();
                    auto& meshComp = meshSystem.addComponent(entity);
                    meshComp.mesh = loadedMesh.mesh;
                    meshComp.material = loadedMesh.material;
                    entity.transform = loadedMesh.transform;
                }
            }
        }

        for (const auto& entry : std::filesystem::directory_iterator(RES("game/entities/enemy")))
        {
            if (entry.path().extension() == ".dae") {
                ModelLoadContext loadContext;
                loadContext.baseTexturePath = "game/entities/enemy";
                loadContext.baseMaterial = engine.lambertMaterial;
                loadModel(entry.path().string(), loadContext);
                for (auto& [_, loadedMesh] : loadContext.meshes)
                {
                    _enemyMesh = loadedMesh.mesh;
                    break;
                }
            }
        }
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
            enemySystem.addComponent(entity);
            auto& meshComp = meshSystem.addComponent(entity);
            meshComp.mesh = _enemyMesh;
            lastSpawnTime = now;
        }
    }

    void Game::draw(Framework::Engine& engine, float deltaTime)
    {
    }
}