#pragma once

#include "framework/api.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <GL/glew.h>

namespace Experiment::Framework 
{
    // -------------------
    // Texture
    // -------------------
    class EXPERIMENT_FRAMEWORK_API Texture {
    private:
        std::string _path;
        GLuint _textureID;
        GLenum _textureTarget;
        static constexpr const char* _supportedExtensions[] = { ".png", ".jpg", ".jpeg", ".bmp", ".tga", ".dds", ".ktx" };

    public:
        Texture(const std::string& path, GLenum textureTarget = GL_TEXTURE_2D);
        ~Texture();

        void useDefaultPinkTexture();

        void bind(GLuint unit = 0) const;
        GLuint getTextureID() const { return _textureID; }
        std::string getPath() const { return _path; }

        static bool isSupportedExtension(const std::string& extension) {
            return std::find(std::begin(_supportedExtensions), std::end(_supportedExtensions), extension) != std::end(_supportedExtensions);
        }        
    };
}
