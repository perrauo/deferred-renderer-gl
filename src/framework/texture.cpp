#include "framework/texture.h"
#include "framework/renderer.h"

#include "stb_image.h"
#include "gli/gli.hpp"
#include "gli/texture.hpp"

#include <GL/glew.h>

#include <iostream>
#include <filesystem>
#include <string>

namespace Experiment::Framework
{
    const unsigned char pinkTextureData[3] = { 255, 0, 255 }; // RGB values for pink


    // -------------------
    // Texture
    // -------------------
    
    // TODO:
    // Modern applications don't use all 32 slots. We should improve this


// Function to check for OpenGL errors
    void checkGLError(const std::string& location) {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error at " << location << ": " << err << std::endl;
        }
    }

    // Example usage in your Texture constructor
    Texture::Texture(const std::string& path, GLenum textureTarget)
        : _path(path)
        , _textureTarget(textureTarget)
    {
        std::filesystem::path filePath(path);
        std::string extension = filePath.extension().string();
        glGenTextures(1, &_textureID);
        glBindTexture(_textureTarget, _textureID);
        checkGLError("glBindTexture");

        if (isSupportedExtension(extension))
        {
            gli::texture texture = gli::load(path);
            if (texture.empty()) {
                std::cout << "Failed to load texture: " << path << std::endl;
                useDefaultPinkTexture();
                return;
            }

            glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            bool isCompressed = gli::is_compressed(texture.format());
            GLenum format;
            if (isCompressed)
            {
                using FormatType = gli::texture::format_type;
                switch (texture.format())
                {
                case FormatType::FORMAT_RGB_DXT1_UNORM_BLOCK8:
                case FormatType::FORMAT_RGB_DXT1_SRGB_BLOCK8:
                case FormatType::FORMAT_RGBA_DXT1_UNORM_BLOCK8:
                case FormatType::FORMAT_RGBA_DXT1_SRGB_BLOCK8:
                    format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                    break;
                case FormatType::FORMAT_RGBA_DXT3_UNORM_BLOCK16:
                case FormatType::FORMAT_RGBA_DXT3_SRGB_BLOCK16:
                    format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                    break;
                case FormatType::FORMAT_RGBA_DXT5_UNORM_BLOCK16:
                case FormatType::FORMAT_RGBA_DXT5_SRGB_BLOCK16:
                    format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                    break;
                default:
                    format = GL_COMPRESSED_RGBA;
                    break;
                }

                if (texture.extent().x <= 0 || texture.extent().y <= 0) {
                    std::cerr << "Invalid texture dimensions." << std::endl;
                    return;
                }


                if (texture.size() == 0) {
                    std::cerr << "Invalid texture data size." << std::endl;
                    return;
                }
                for (std::size_t level = 0; level < texture.levels(); ++level)
                {
                    glCompressedTexImage2D(_textureTarget, level, format, texture.extent(level).x, texture.extent(level).y, 0, texture.size(level), texture.data(0, 0, level));
                    checkGLError("glCompressedTexImage2D");
                }
            }
            else
            {
                format = GL_RGBA;
                glTexImage2D(_textureTarget, 0, format, texture.extent().x, texture.extent().y, 0, format, GL_UNSIGNED_BYTE, texture.data());
                checkGLError("glTexImage2D");
            }
            glGenerateMipmap(_textureTarget);
            checkGLError("glGenerateMipmap");
        }
        else
        {
            useDefaultPinkTexture();
        }
    }

    void Texture::useDefaultPinkTexture()
    {
        glTexImage2D(_textureTarget, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, pinkTextureData);
        glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &_textureID);
    }

    void Texture::bind(GLuint unit) const {

        using namespace DeferredShading;

        // GL_TEXTURE0 reserved by the deferred renderer. So let's use the texture slots afterward
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(_textureTarget, _textureID);
    }
}