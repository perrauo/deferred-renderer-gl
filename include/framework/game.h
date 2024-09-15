#pragma once

#include "framework/api.h"

namespace Experiment::Framework
{
    class Engine;

    class EXPERIMENT_FRAMEWORK_API IGame {
    public:
        virtual void start(Engine& engine) {}
        virtual void update(Engine& engine, float deltaTime) {}
        virtual void draw(Engine& engine, float deltaTime) {}
    };
}
