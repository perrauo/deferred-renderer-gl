#include <iostream>

#include "framework/engine.h"
#include "framework/material.h"

#include "game/game.h"

int main()
{
    using namespace Experiment::Demo;
    using namespace Experiment::Framework;
  
    // Create an instance of the Engine class    
    Engine engine;
    
    // Just opens the window
    engine.setup();

    engine.startGame(std::make_unique<DemoGame>());

    engine.loop();

    return 0;
}
