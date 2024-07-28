#include "framework/material.h"
#include "framework/texture.h"
#include "framework/utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GhostGame::Framework
{
    // -------------------
    // Shader
    // -------------------

    Shader::Shader(const std::string& name, const std::string& shaderPath, GLenum shaderType)
        : _name(name)
        , _shaderType(shaderType)
    {
        _shaderId = glCreateShader(_shaderType);

        // Read Shader from file
        std::ifstream shaderFile(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        std::string shaderSource = shaderStream.str();
        shaderFile.close();

        // Shader
        const char* shaderSourceCStr = shaderSource.c_str();
        glShaderSource(_shaderId, 1, &shaderSourceCStr, nullptr);
        glCompileShader(_shaderId);
    }

    Shader::~Shader()
    {
        glDeleteShader(_shaderId);
    }

    // -------------------
    // Material
    // -------------------

    Material::Material(
        const std::string& name,
        const std::string& shaderPath
    ) :
        Material(
            name
            , shaderPath + ".vert"
            , shaderPath + ".frag"
        )
    {
    }

    Material::Material(
        const std::string& name,
        const std::string& vertexPath,
        const std::string& fragmentPath
    )
        : _name(name)
    {
        _programId = glCreateProgram();

        // Read Vertex Shader from file
        std::ifstream vertexFile(vertexPath);
        std::stringstream vertexStream;
        vertexStream << vertexFile.rdbuf();
        std::string vertexSource = vertexStream.str();
        vertexFile.close();

        // Vertex Shader
        _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexSourceCStr = vertexSource.c_str();
        glShaderSource(_vertexShaderId, 1, &vertexSourceCStr, nullptr);
        glCompileShader(_vertexShaderId);
        glAttachShader(_programId, _vertexShaderId);

        // Read Fragment Shader from file
        std::ifstream fragmentFile(fragmentPath);
        std::stringstream fragmentStream;
        fragmentStream << fragmentFile.rdbuf();
        std::string fragmentSource = fragmentStream.str();
        fragmentFile.close();

        // Fragment Shader
        _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentSourceCStr = fragmentSource.c_str();
        glShaderSource(_fragmentShaderId, 1, &fragmentSourceCStr, nullptr);
        glCompileShader(_fragmentShaderId);
        glAttachShader(_programId, _fragmentShaderId);

        glLinkProgram(_programId);
    }

    Material::~Material()
    {
        glDeleteShader(_vertexShaderId);
        glDeleteShader(_fragmentShaderId);
        glDeleteProgram(_programId);
    }

    void Material::setUniform(const std::string& name, float value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        glUniform1f(location, value);
    }

    void Material::setUniform(const std::string& name, int value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        glUniform1i(location, value);
    }

    void Material::setUniform(const std::string& name, const glm::vec2& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        glUniform2fv(location, 1, glm::value_ptr(value));
    }

    void Material::setUniform(const std::string& name, const glm::vec3& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        glUniform3fv(location, 1, glm::value_ptr(value));
    }

    void Material::setUniform(const std::string& name, const glm::vec4& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        glUniform4fv(location, 1, glm::value_ptr(value));
    }

    void Material::setUniform(const std::string& name, const glm::mat4& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }


    void Material::use()
    {
        glUseProgram(_programId);
    }

    // -------------------
    // MaterialInstance
    // -------------------

    void MaterialInstance::setUniform(const std::string& name, float value)
    {
        _floatUniforms[name] = value;
    }

    void MaterialInstance::setUniform(const std::string& name, int value)
    {
        _intUniforms[name] = value;
    }

    void MaterialInstance::setUniform(const std::string& name, const std::weak_ptr<Texture>& texture)
    {
        _textureUniforms[name] = texture;
    }

    void MaterialInstance::setUniform(const std::string& name, const glm::vec2& value)
    {
        _vec2Uniforms[name] = value;
    }

    void MaterialInstance::setUniform(const std::string& name, const glm::vec3& value)
    {
        _vec3Uniforms[name] = value;
    }

    void MaterialInstance::setUniform(const std::string& name, const glm::vec4& value)
    {
        _vec4Uniforms[name] = value;
    }

    void MaterialInstance::setUniform(const std::string& name, const glm::mat4& value)
    {
        _mat4Uniforms[name] = value;
    }

    void MaterialInstance::use()
    {
        if (auto material = _material.lock())
        {
            material->use();

            // Set the uniforms
            for (const auto& uniform : _floatUniforms) {
                material->setUniform(uniform.first, uniform.second);
            }
            for (const auto& uniform : _intUniforms) {
                material->setUniform(uniform.first, uniform.second);
            }
            for (const auto& uniform : _vec2Uniforms) {
                material->setUniform(uniform.first, uniform.second);
            }
            for (const auto& uniform : _vec3Uniforms) {
                material->setUniform(uniform.first, uniform.second);
            }
            for (const auto& uniform : _mat4Uniforms) {
                material->setUniform(uniform.first, uniform.second);
            }

            // Set the texture uniforms
            int textureUnit = 0;
            for (const auto& textureUniform : _textureUniforms) {
                if (auto texture = textureUniform.second.lock()) {
                    texture->bind(textureUnit);
                    material->setUniform(textureUniform.first, textureUnit);
                    textureUnit++;
                }
            }
        }
    }
}