#pragma once

#include "framework/api.h"
#include "framework/utils.h"

#include <string>
#include <memory>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace GhostGame::Framework
{
    class Texture;    

    namespace Materials
    {
        namespace Lambert
        {
            constexpr char name[] = NAMEOF(Lambert);

            namespace Uniforms
            {
                constexpr char textureSampler[] = "textureSampler";
                constexpr char modelMatrix[] = "modelMatrix";
                constexpr char viewMatrix[] = "viewMatrix";
                constexpr char projectionMatrix[] = "projectionMatrix";
                constexpr char matterialDiffuse[] = "materialDiffuse";
                constexpr char lightDirection[] = "lightDirection";
                constexpr char lightColor[] = "lightColor";
            }

            namespace Attributes
            {
                constexpr char vertexPosition[] = "vertexPosition";
                constexpr char vertexNormal[] = "vertexNormal";
                constexpr char vertexUv[] = "vertexUv";
            }

            namespace Varying
            {
                constexpr char normal[] = "normal";
                constexpr char uv[] = "uv";
            }
        }
    }


    // -------------------
    // Shader
    // -------------------


    class GHOSTGAME_FRAMEWORK_API Shader
    {
    private:
        GLuint _shaderId;
        std::string _name;
        GLenum _shaderType;

    public:
        Shader(const std::string& name, const std::string& shaderPath, GLenum shaderType);
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        ~Shader();

        GLuint getShaderId() const { return _shaderId; }
        std::string getName() const { return _name; }
        GLenum getShaderType() const { return _shaderType; }
    };


    // -------------------
    // IMaterial
    // -------------------

    class GHOSTGAME_FRAMEWORK_API IMaterial 
    {
    public:
        
        virtual void use() = 0;

        virtual GLuint getProgramId() const = 0;

        virtual std::string getName() const = 0;

    };

    // -------------------
    // Material
    // -------------------

    class GHOSTGAME_FRAMEWORK_API Material : public IMaterial
    {
    private:
        GLuint _programId;
        GLuint _vertexShaderId;
        GLuint _fragmentShaderId;
        std::string _name;

    public:

        Material(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        
        /// <summary>
        /// Alternate constructore that appends .vert, .frag to the given path
        /// </summary>
        /// <param name="name"></param>
        /// <param name="shaderPath"></param>
        Material(const std::string& name, const std::string& shaderPath);

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        ~Material();

        void use() override;

        virtual std::string getName() const override { return _name; }

        GLuint getProgramId() const override { return _programId; }

        void setUniform(const std::string& name, float value);

        void setUniform(const std::string& name, int value);

        void setUniform(const std::string& name, const glm::vec2& value);

        void setUniform(const std::string& name, const glm::vec3& value);

        void setUniform(const std::string& name, const glm::vec4& value);

        void setUniform(const std::string& name, const glm::mat4& value);

        void setUniform(const std::string& name, const std::weak_ptr<Texture>& texture);
    };

    // -------------------
    // MaterialInstance
    // -------------------

    class GHOSTGAME_FRAMEWORK_API MaterialInstance : public IMaterial
    {
    public:
        MaterialInstance(const std::shared_ptr<Material>& material) : _material(material) {}

        ~MaterialInstance() = default;

        MaterialInstance(const MaterialInstance&) = delete;
        MaterialInstance& operator=(const MaterialInstance&) = delete;
        
        void setUniform(const std::string& name, float value);

        void setUniform(const std::string& name, int value);

        void setUniform(const std::string& name, const glm::vec2& value);

        void setUniform(const std::string& name, const glm::vec3& value);

        void setUniform(const std::string& name, const glm::vec4& value);

        void setUniform(const std::string& name, const glm::mat4& value);

        void setUniform(const std::string& name, const std::weak_ptr<Texture>& value);

        void use() override;

        GLuint getProgramId() const override
        {
            if (auto material = _material.lock())
            {
                return material->getProgramId();
            }
            return GLuint(-1);
        }

        std::string getName() const override
        {
            if (auto material = _material.lock())
            {
                return material->getName();
            }
            return "";
        }

    private:
        std::weak_ptr<Material> _material;
        std::unordered_map<std::string, std::weak_ptr<Texture>> _textureUniforms;
        std::unordered_map<std::string, float> _intUniforms;
        std::unordered_map<std::string, float> _floatUniforms;
        std::unordered_map<std::string, glm::vec2> _vec2Uniforms;
        std::unordered_map<std::string, glm::vec3> _vec3Uniforms;
        std::unordered_map<std::string, glm::vec4> _vec4Uniforms;
        std::unordered_map<std::string, glm::mat4> _mat4Uniforms;
    };

}