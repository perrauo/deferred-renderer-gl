#pragma once

#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#elif __linux__
#include <unistd.h>
#endif

#include <regex>

#define NAMEOF(x) #x

namespace GhostGame::Framework
{
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

#define RES(relativePath) ::GhostGame::Framework::getResPath(relativePath)