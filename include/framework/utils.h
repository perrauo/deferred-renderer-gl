#pragma once

#include <GL/glew.h>

#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#elif __linux__
#include <unistd.h>
#endif

#include <regex>
#include "framework/preprocessor.h"

#define NAMEOF(x) #x

namespace Experiment::Framework
{
    constexpr GLfloat cubeVertices[] = {
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f, 
    1.0f,  1.0f, -1.0f, 
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f, 
    1.0f, -1.0f,  1.0f, 
    1.0f,  1.0f,  1.0f, 
    -1.0f,  1.0f,  1.0f, 
    };

    // Cube indices
    constexpr GLuint cubeIndices[] = {
        0, 1, 2, 2, 3, 0, // Front face
        4, 5, 6, 6, 7, 4, // Back face
        0, 1, 5, 5, 4, 0, // Bottom face
        2, 3, 7, 7, 6, 2, // Top face
        0, 3, 7, 7, 4, 0, // Left face
        1, 2, 6, 6, 5, 1  // Right face
    };

    constexpr char vertexShaderSource[] =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n";

    constexpr char fragmentShaderSource[] =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        // Pink color
        "FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
        "}\n";

    inline std::string getResPath(const std::string& relativePath)
    {
        std::filesystem::path executablePath;

#ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);
        executablePath = std::filesystem::path(buffer).parent_path();
#elif __APPLE__
        char buffer[1024];
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) == 0)
            executablePath = std::filesystem::path(buffer).parent_path();
#elif __linux__
        char buffer[1024];
        ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer));
        executablePath = std::filesystem::path(std::string(buffer, count > 0 ? count : 0)).parent_path();
#endif

        std::string modifiedRelativePath = relativePath;     
        if (
            !modifiedRelativePath.empty() && 
            (modifiedRelativePath[0] == '\\' || modifiedRelativePath[0] == '/')            
            )
        {
            modifiedRelativePath = modifiedRelativePath.substr(1);
        }

        modifiedRelativePath = std::regex_replace(modifiedRelativePath, std::regex("\\/\\/+"), "/");

        std::filesystem::path newPath = executablePath / "resources" / modifiedRelativePath;
        return newPath.string();
    }
}

#define RES(relativePath) ::Experiment::Framework::getResPath(relativePath)