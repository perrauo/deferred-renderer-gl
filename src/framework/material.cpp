#include "framework/material.h"
#include "framework/texture.h"
#include "framework/utils.h"
#include "framework/engine.h"
#include "framework/renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Experiment::Framework
{
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

        GLint isCompiled = 0;
        glGetShaderiv(_vertexShaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(_vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(_vertexShaderId, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            std::cerr << "Vertex Shader compilation error: " << &errorLog[0] << std::endl;

            // Exit with failure.
            glDeleteShader(_vertexShaderId); // Don't leak the shader.
            return;
        }

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

        isCompiled = 0;
        glGetShaderiv(_fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(_fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(_fragmentShaderId, maxLength, &maxLength, &errorLog[0]);

            std::cerr << "Fragment Shader compilation error: " << &errorLog[0] << std::endl;

            glDeleteShader(_fragmentShaderId);
            glDeleteShader(_vertexShaderId);
            return;
        }

        glAttachShader(_programId, _fragmentShaderId);

        glLinkProgram(_programId);
        // Check for linking errors
        GLint isLinked = 0;
        glGetProgramiv(_programId, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(_programId, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manner you deem best.
            std::cerr << "Shader linking error: " << &errorLog[0] << std::endl;

            // Exit with failure.
            glDeleteProgram(_programId); // Don't leak the program.
            return;
        }
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
        if (location != -1)
        {
            glUniform1f(location, value);
        }
    }

    void Material::setUniform(const std::string& name, int value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        if (location != -1)
        {
            glUniform1i(location, value);
        }
    }

    void Material::setUniform(const std::string& name, ReservedTextureSlot value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        if (location != -1)
        {
            glUniform1i(location, (int)value);
        }
    }

    void Material::setUniform(const std::string& name, const glm::vec2& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        if (location != -1)
        {
            glUniform2fv(location, 1, glm::value_ptr(value));
        }
    }

    void Material::setUniform(const std::string& name, const glm::vec3& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        if (location != -1)
        {
            glUniform3fv(location, 1, glm::value_ptr(value));
        }
    }

    void Material::setUniform(const std::string& name, const glm::vec4& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        if (location != -1)
        {
            glUniform4fv(location, 1, glm::value_ptr(value));
        }
    }

    void Material::setUniform(const std::string& name, const glm::mat4& value)
    {
        GLuint location = glGetUniformLocation(_programId, name.c_str());
        if (location != -1)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        }
    }

    void Material::bind(Engine& engine)
    {
        glUseProgram(_programId);
        engine.programStack.push(_programId);
    }

    void Material::unbind(Engine& engine)
    {        
        if (GLuint previousShaderId = engine.programStack.top())
        {
            engine.programStack.pop();
            previousShaderId = engine.programStack.top();
            glUseProgram(previousShaderId);
            return;
        }       
        glUseProgram(0);
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

    void MaterialInstance::setUniform(const std::string& name, ReservedTextureSlot value)
    {
        _intUniforms[name] = (int)value;
    }

    void MaterialInstance::setUniform(const std::string& name, const std::shared_ptr<Texture>& texture)
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

    void MaterialInstance::unbind(Engine& engine)
    {
        if (auto material = _material)
        {
            material->unbind(engine);
        }
    }

    void MaterialInstance::bind(Engine& engine)
    {        
        if (auto material = _material)
        {
            material->bind(engine);

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
            using namespace DeferredShading;
            int textureUnit = numTexturesReserved;
            for (const auto& textureUniform : _textureUniforms) {
                if (auto texture = textureUniform.second) {
                    texture->bind(textureUnit);
                    material->setUniform(textureUniform.first, textureUnit);
                    textureUnit++;
                }
            }
        }
    }
}