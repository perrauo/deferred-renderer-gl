#include "framework/shader.h"

namespace GhostGame::Framework
{
    Shader::Shader(const std::string& source)
    {
        // Create a shader object
        _shaderID = glCreateShader(GL_VERTEX_SHADER);

        // Set the source code for the shader
        const char* sourceCStr = source.c_str();
        glShaderSource(_shaderID, 1, &sourceCStr, nullptr);

        // Compile the shader
        glCompileShader(_shaderID);

        // TODO: Add error checking here to make sure the shader compiled successfully
    }

    void Shader::use()
    {
        glUseProgram(_shaderID);
    }

    Shader::~Shader()
    {
        // Delete the shader when we're done with it
        glDeleteShader(_shaderID);
    }
}