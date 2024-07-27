#pragma once

#include "framework/game.h"

#include <memory>


namespace GhostGame
{
    namespace Framework
    {
        class Mesh;
    }

    using EntityId = int;

    class Game : public Framework::IGame
    {
    public:

        Game() = default;

        ~Game() = default;

        void start(Framework::Engine& engine) override;

        void update(Framework::Engine& engine, float deltaTime) override;

        void render(Framework::Engine& engine) override;

        EntityId playerId = -1;

        std::shared_ptr<Framework::Mesh> enemyModel;

        float enemySpawnFrequency = -1;
    };
}

