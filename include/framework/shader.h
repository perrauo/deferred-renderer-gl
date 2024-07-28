#pragma once

#include "framework/api.h"

#include <string>
#include <GL/glew.h>

namespace GhostGame::Framework
{
    class GHOSTGAME_FRAMEWORK_API Shader 
    {
    public:
        Shader(const std::string& source);

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        ~Shader();

        void use();

    private:
        GLuint _shaderID;
    };
}