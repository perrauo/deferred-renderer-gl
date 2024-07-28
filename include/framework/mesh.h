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

namespace GhostGame::Framework
{
    class Material;
    class MaterialInstance;
    class Engine;

    // -------------------
    // Mesh
    // -------------------

    class GHOSTGAME_FRAMEWORK_API Mesh {

        GLuint VAO = 0, VBO = 0, EBO = 0;        
    public:

        bool isLoaded = false;
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;


        // Constructor
        Mesh();
        Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
        Mesh(const std::string& path); // New constructor for loading .dae files
        ~Mesh();

        // Render the mesh
        void draw() const;

        // Initialize the mesh
        void loadMesh();

        void unloadMesh();
    };   

    // -------------------
    // MeshComponent
    // -------------------

    class GHOSTGAME_FRAMEWORK_API MeshComponent : public Component
    {
    public:
        std::shared_ptr<Mesh> mesh;

        std::shared_ptr<MaterialInstance> material;

        void start(Framework::Engine& engine, Framework::Entity& entity) override;
        void update(Engine& engine, Entity& entity, float deltaTime) override;
    };
}
