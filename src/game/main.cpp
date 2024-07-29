#include <iostream>

#include "framework/engine.h"
#include "framework/material.h"

#include "game/game.h"

int main()
{
    using namespace GhostGame;
    using namespace GhostGame::Framework;
  

    // Create an instance of the Engine class    
    Engine engine;
    
    // Just opens the window
    engine.setup();

    std::unique_ptr<Game> game = std::make_unique<Game>();
    engine.startGame(std::move(game));    

    engine.loop();

    return 0;
}
