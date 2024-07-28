#pragma once

#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#elif __linux__
#include <unistd.h>
#endif

namespace GhostGame
{
    inline std::string getPathToCurrent(const std::string& relativePath)
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

        std::filesystem::path newPath = executablePath / std::filesystem::path(relativePath);
        return newPath.string();
    }
}
