#pragma once

#include "framework/game.h"

namespace GhostGame
{
    class Game : public Framework::IGame
    {
        void Start(Framework::Engine& engine) override;

        void Update(Framework::Engine& engine) override;

        void Render(Framework::Engine& engine) override;

        ~Game() override;
    };
}

