#pragma once

#include "framework/api.h"
#include "framework/component.h"

#include <vector>
#include <string>
#include <memory>

#include <GL/glew.h>
#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

struct aiNode;
struct aiScene;
struct aiMesh;

namespace GhostGame::Framework
{
    class GHOSTGAME_FRAMEWORK_API Mesh {
    public:
        // Constructor
        Mesh();
        Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
        Mesh(const std::string& path); // New constructor for loading .dae files
        ~Mesh();

        // Render the mesh
        void draw() const;

        // Load mesh from file
        void loadModel(const std::string& path);

    private:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        GLuint VAO, VBO, EBO;

        // Initialize the mesh
        void initModel();

        // Process a node in the scene
        void processNode(aiNode* node, const aiScene* scene);

        // Process a mesh in the scene
        void processMesh(aiMesh* mesh, const aiScene* scene);
    };

    class GHOSTGAME_FRAMEWORK_API MeshRenderer : public Component
    {
    public:
        std::shared_ptr<Mesh> mesh;

        MeshRenderer(const std::shared_ptr<Mesh>& mesh)
        : mesh(mesh)
        {
        }

        virtual void update(Engine& engine, float deltaTime) {
        }
    };
}
