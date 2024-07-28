#pragma once

#include "framework/game.h"
#include "framework/camera.h"
#include "game/player.h"

#include <memory>
#include <unordered_map>

namespace GhostGame
{
    namespace Framework
    {
        using EntityId = int;
        class Mesh;
        class MeshComponent;
        class Material;
    }

    class EnemyComponent;
    class PlayerComponent;

    class Game : public Framework::IGame
    {

    private:

        Framework::EntityId _playerId = -1;

        std::shared_ptr<Framework::Mesh> _enemyMesh;

        std::shared_ptr<Framework::Material> _lambertMaterial;

        float _enemySpawnFrequency = -1;

    public:
        
        // Pseudo ECS

        PlayerComponent player;
        Framework::CameraComponent camera;

        // Enemies  

        Game() = default;

        ~Game() = default;

        void start(Framework::Engine& engine) override;

        void update(Framework::Engine& engine, float deltaTime) override;

        void render(Framework::Engine& engine) override;
    };
}

