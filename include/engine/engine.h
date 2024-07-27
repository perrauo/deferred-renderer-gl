#ifndef GHOSTGAME_ENGINE_H
#define GHOSTGAME_ENGINE_H

#include "engine/renderer.h"
#include "engine/api.h"

namespace GhostGame
{
    class GHOSTGAME_ENGINE_API  Engine {
    private:
        Renderer renderer;
        bool isRunning;

    public:
        Engine();

        void Start();

        void ProcessInput();

        void Update();

        void Stop();
    };
}


#endif