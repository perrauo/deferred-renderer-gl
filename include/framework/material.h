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
    class Engine;
    enum class GBufferSlot : int;

    namespace Materials
    {
        namespace Uniforms
        {
            constexpr char position[] = "position";
            constexpr char model[] = "model";
            constexpr char view[] = "view";
            constexpr char projection[] = "projection";
            constexpr char textureSampler[] = "textureSampler";
            constexpr char screenSize[] = "screenSize";
        }
        namespace Attributes
        {
            constexpr char position[] = "position";
            constexpr char normal[] = "normal";
            constexpr char uv[] = "uv";
        }

        namespace Outputs
        {
            constexpr char outNormal[] = "outNormal";
            constexpr char outUv[] = "outUv";
        }
        namespace Varying
        {
            constexpr char normal[] = "normal";
            constexpr char uv[] = "uv";
        }

        namespace Lambert
        {
            constexpr char name[] = NAMEOF(Lambert);

            namespace Uniforms
            {
                constexpr char diffuseColor[] = "diffuseColor";
                constexpr char lightDirection[] = "lightDirection";
                constexpr char lightColor[] = "lightColor";
                constexpr char lightIntensity[] = "lightIntensity";
                constexpr char textureDiffuse[] = "textureDiffuse";
            }
        }
    }


    // -------------------
    // IMaterial
    // -------------------

    class GHOSTGAME_FRAMEWORK_API IMaterial 
    {
    public:
        
        virtual void bind(Engine& engine) = 0;

        virtual void unbind(Engine& engine) = 0;

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

        void bind(Engine& engine) override;

        void unbind(Engine& engine) override;

        virtual std::string getName() const override { return _name; }

        GLuint getProgramId() const override { return _programId; }

        void setUniform(const std::string& name, float value);

        void setUniform(const std::string& name, int value);

        void setUniform(const std::string& name, GBufferSlot value);

        void setUniform(const std::string& name, const glm::vec2& value);

        void setUniform(const std::string& name, const glm::vec3& value);

        void setUniform(const std::string& name, const glm::vec4& value);

        void setUniform(const std::string& name, const glm::mat4& value);

        void setUniform(const std::string& name, const std::shared_ptr<Texture>& texture);
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

        void setUniform(const std::string& name, GBufferSlot value);

        void setUniform(const std::string& name, const glm::vec2& value);

        void setUniform(const std::string& name, const glm::vec3& value);

        void setUniform(const std::string& name, const glm::vec4& value);

        void setUniform(const std::string& name, const glm::mat4& value);

        void setUniform(const std::string& name, const std::shared_ptr<Texture>& value);

        void bind(Engine& engine) override;

        void unbind(Engine& engine) override;

        GLuint getProgramId() const override
        {
            if (auto material = _material)
            {
                return material->getProgramId();
            }
            return GLuint(-1);
        }

        std::string getName() const override
        {
            if (auto material = _material)
            {
                return material->getName();
            }
            return "";
        }

    private:
        std::shared_ptr<Material> _material;
        std::unordered_map<std::string, std::shared_ptr<Texture>> _textureUniforms;
        std::unordered_map<std::string, float> _intUniforms;
        std::unordered_map<std::string, float> _floatUniforms;
        std::unordered_map<std::string, glm::vec2> _vec2Uniforms;
        std::unordered_map<std::string, glm::vec3> _vec3Uniforms;
        std::unordered_map<std::string, glm::vec4> _vec4Uniforms;
        std::unordered_map<std::string, glm::mat4> _mat4Uniforms;
    };

}