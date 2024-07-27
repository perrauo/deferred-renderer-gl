#pragma once

#include "framework/game.h"

class Avatar;

namespace GhostGame
{
    class Game : public Framework::IGame
    {
    public:
        void start(Framework::Engine& engine) override;

        void update(Framework::Engine& engine, float deltaTime) override;

        void render(Framework::Engine& engine) override;

        ~Game() override;

        std::shared_ptr<Avatar> avatar;
    };
}

