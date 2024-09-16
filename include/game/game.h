#pragma once

#include "framework/game.h"
#include "framework/camera.h"
#include "game/player.h"

#include <memory>
#include <unordered_map>
#include <boost/json.hpp>

namespace Experiment::Framework
{
    ;
    class Mesh;
    class MeshComponent;
    class Material;
    class MaterialProxy;
    class Texture;
}

namespace Experiment::Demo
{
    class EnemyComponent;
    class PlayerComponent;

    class DemoGame : public Framework::IGame
    {

    private:

        int _playerId = -1;
        std::shared_ptr<Framework::Mesh> _enemyMesh;
        std::shared_ptr<Framework::MaterialProxy> _enemyMaterial;
        float _enemySpawnFrequency = -1;
        glm::vec2 _enemySpawnDistance = { 10, 10 };
        std::shared_ptr<Framework::Texture> _pinkTexture;

    public:        

        boost::json::value config;

        DemoGame() = default;

        ~DemoGame() = default;

        void start(Framework::Engine& engine) override;

        void update(Framework::Engine& engine, float deltaTime) override;

        void draw(Framework::Engine& engine, float deltaTime) override;
    };
}

