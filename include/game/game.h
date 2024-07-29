#pragma once

#include "framework/game.h"
#include "framework/camera.h"
#include "game/player.h"

#include <memory>
#include <unordered_map>
#include <boost/json.hpp>

namespace GhostGame
{
    namespace Framework
    {
        using EntityId = int;
        class Mesh;
        class MeshComponent;
        class Material;
        class MaterialInstance;
    }

    class EnemyComponent;
    class PlayerComponent;

    class Game : public Framework::IGame
    {

    private:

        Framework::EntityId _playerId = -1;
        std::shared_ptr<Framework::Mesh> _enemyMesh;
        std::shared_ptr<Framework::MaterialInstance> _enemyGeomMaterial;
        std::shared_ptr<Framework::MaterialInstance> _enemyLightMaterial;
        float _enemySpawnFrequency = -1;
        glm::vec2 _enemySpawnDistance = { 10, 10 };

    public:        

        boost::json::value config;

        Game() = default;

        ~Game() = default;

        void start(Framework::Engine& engine) override;

        void update(Framework::Engine& engine, float deltaTime) override;

        void draw(Framework::Engine& engine, float deltaTime) override;
    };
}

