#include "framework/texture.h"
#include "framework/renderer.h"

#include "stb_image.h"
#include "gli/gli.hpp"
#include "gli/texture.hpp"

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

    Texture::Texture(const std::string& path, GLenum textureTarget)
        : _path(path)
        , _textureTarget(textureTarget)
    {
        std::filesystem::path filePath(path);
        std::string extension = filePath.extension().string();
        glGenTextures(1, &_textureID);
        glBindTexture(_textureTarget, _textureID);

        if (isSupportedExtension(extension))
        {
            if (extension == ".dds")
            {
                gli::texture Texture = gli::load(path);
                if (Texture.empty()) {
                    std::cout << "Failed to load texture: " << path << std::endl;
                    useDefaultPinkTexture();
                    return;
                }

                GLenum format = gli::is_compressed(Texture.format()) ? GL_COMPRESSED_RGBA : GL_RGBA;
                glTexImage2D(_textureTarget, 0, format, Texture.extent().x, Texture.extent().y, 0, format, GL_UNSIGNED_BYTE, Texture.data());
                glGenerateMipmap(_textureTarget);
                glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            else
            {
                int width, height, channels;
                unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
                if (data) {
                    GLenum format = channels == 3 ? GL_RGB : GL_RGBA;
                    glTexImage2D(_textureTarget, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(_textureTarget);
                    glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    stbi_image_free(data);
                }
                else {
                    std::cout << "Failed to load texture: " << path << std::endl;
                    useDefaultPinkTexture();
                }
            }
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
        glActiveTexture(GL_TEXTURE0 + numTexturesReserved + unit);
        glBindTexture(_textureTarget, _textureID);
    }
}