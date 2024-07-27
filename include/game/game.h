#pragma once

#include "framework/game.h"

namespace GhostGame
{
    class Game : public Framework::IGame
    {
        void start(Framework::Engine& engine) override;

        void update(Framework::Engine& engine) override;

        void render(Framework::Engine& engine) override;

        ~Game() override;
    };
}

