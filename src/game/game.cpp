#include "game/game.h"
#include "game/types.h"

#include "framework/engine.h"
#include "framework/model.h"
#include "framework/mesh.h"
#include "framework/material.h"
#include "framework/entity.h"
#include "framework/utils.h"
#include "framework/light.h"
#include "framework/texture.h"

#include <glm/gtc/random.hpp>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <iterator>
#include <boost/json.hpp>

namespace Experiment::Demo
{
    void DemoGame::start(Framework::Engine& engine)
    {
        using namespace Framework;

        std::ifstream file(RES("game/config.json"));
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        config = boost::json::parse(content);
        auto& enemy = config.at("Enemy").as_object();;
        _enemySpawnFrequency = enemy.at("spawnFrequency").as_double();
        auto& spawnDistance = enemy.at("spawnDistance");
        _enemySpawnDistance = { spawnDistance.at("min").as_double(), spawnDistance.at("max").as_double() };
        _pinkTexture = std::make_shared<Texture>("");

        auto& directionalLights = engine.addSystem<DirectionalLightSystem>();
        auto& directionalLightEntity = engine.spawnEntity();
        directionalLightEntity.transform.position = glm::vec3(0.0f, 5.0f, 5.0f);
        directionalLightEntity.transform.rotation = glm::quat(glm::vec3(-glm::radians(45.0f), 0.0f, 0.0f));
        directionalLightEntity.transform.scale = glm::vec3(1.0f);
        auto& directionalLight = directionalLights.addComponent(directionalLightEntity);
        directionalLight.type = LightType::Directional;

        auto& pointLights = engine.addSystem<PointLightSystem>();
        auto& pointLightEntity = engine.spawnEntity();
        pointLightEntity.transform.position = glm::vec3(0, 0, 0);
        auto& pointLight = pointLights.addComponent(pointLightEntity);
        pointLight.type = LightType::Point;

        _playerId = engine.spawnEntity();
        auto& playerSystem = engine.addSimpleSystem<PlayerComponent>();
        auto& cameraSystem = engine.addSimpleSystem<CameraComponent>();
        playerSystem.addComponent(_playerId);
        cameraSystem.addComponent(_playerId);
        
        auto& meshSystem = engine.addSimpleSystem<MeshComponent>();
        engine.addSimpleSystem<EnemyComponent>();

        for (const auto& entry : std::filesystem::directory_iterator(RES("game/environment")))
        {
            if (entry.path().extension() == ".dae") {
                ModelLoadContext loadContext{ .engine = engine };
                loadContext.baseTexturePath = "game/environment";
                loadContext.materialType = MaterialType::Lambert;
                loadContext.defaultTexture = _pinkTexture;
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
                ModelLoadContext loadContext{ .engine = engine };
                loadContext.baseTexturePath = "game/entities/enemy";
                loadContext.materialType = MaterialType::Lambert;
                loadContext.defaultTexture = _pinkTexture;
                loadModel(entry.path().string(), loadContext);
                for (auto& [_, loadedMesh] : loadContext.meshes)
                {
                    _enemyMesh = loadedMesh.mesh;
                    _enemyMaterial = loadedMesh.material;
                    break;
                }
            }
        }
    }

    void DemoGame::update(Framework::Engine& engine, float deltaTime)
    {
        using namespace Framework;

        auto& enemySystem = engine.getSimpleSystem<EnemyComponent>();
        auto& meshSystem = engine.getSimpleSystem<MeshComponent>();

        static auto lastSpawnTime = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastSpawnTime);


        if (duration.count() >= _enemySpawnFrequency) {
            auto& player = engine.getEntity(_playerId);
            auto& entity = engine.spawnEntity();

            // Calculate a random position around the player
            float radius = glm::linearRand(_enemySpawnDistance.x, _enemySpawnDistance.y); // adjust this value to change the spawn distance
            float angle = glm::radians(glm::linearRand(0.0f, 360.0f));
            glm::vec3 spawnPosition = player.transform.position + glm::vec3(radius * cos(angle), 0, radius * sin(angle));

            entity.transform.position = spawnPosition;

            // Make the enemy face the player
            glm::vec3 direction = glm::normalize(player.transform.position - spawnPosition);
            entity.transform.rotation = glm::quatLookAt(direction, glm::vec3(0, 1, 0));

            auto& enemyComp = enemySystem.addComponent(entity);
            auto& meshComp = meshSystem.addComponent(entity);
            meshComp.mesh = _enemyMesh;
            meshComp.material = _enemyMaterial;
            lastSpawnTime = now;
        }
    }


    void DemoGame::draw(Framework::Engine& engine, float deltaTime)
    {
    }
}