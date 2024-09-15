#pragma once

#include "framework/api.h"
#include "framework/entity.h"

#include <vector>
#include <string>
#include <memory>

#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include <GL/glew.h>

struct aiNode;
struct aiScene;
struct aiMesh;

namespace Experiment::Framework
{
    class Material;
    class MaterialProxy;
    class Engine;
    enum class MaterialType : int;

    // -------------------
    // Mesh
    // -------------------

    class EXPERIMENT_FRAMEWORK_API Mesh {

        GLuint VAO = 0
        // normals
        , NBO = 0
        // uvs
        , UBO = 0
        , VBO = 0
        , EBO = 0;

        bool _isLoaded = false;
    public:

        // vec3
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        // vec2
        std::vector<GLfloat> uvs;
        // uint
        std::vector<GLuint> indices;


        // Constructor
        Mesh();
        Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
        Mesh(const std::string& path); // New constructor for loading .dae files
        ~Mesh();

        // Render the mesh
        void draw() const;

        void load();

        void unload();
    };   

    // -------------------
    // MeshComponent
    // -------------------

    class EXPERIMENT_FRAMEWORK_API MeshComponent : public Component
    {
    public:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<MaterialProxy> material;

        void start(Framework::Engine& engine, Framework::Entity& entity) override;
        void update(Engine& engine, Entity& entity, float deltaTime) override;
        void draw(Engine& engine, Entity& entity, float deltaTime) override;
    };
}
