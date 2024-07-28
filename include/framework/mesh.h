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
    class Shader;
    class Engine;

    class GHOSTGAME_FRAMEWORK_API Mesh {

        GLuint VAO = 0, VBO = 0, EBO = 0;
    public:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;


        // Constructor
        Mesh();
        Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
        Mesh(const std::string& path); // New constructor for loading .dae files
        ~Mesh();

        // Render the mesh
        void draw() const;

        // Load mesh from file
        void loadModel(const std::string& path);

        // Initialize the mesh
        void initModel();
    };

    struct ModelLoadResult
    {
        std::unique_ptr<Mesh> mesh;

        unsigned int materialIdx = -1;

        std::string texturePath;
    };

    struct ModelLoadContext
    {
        std::unordered_map<int, ModelLoadResult> results;

    };

    struct ModelLoadNodeContext
    {
        std::unordered_map<int, ModelLoadResult> results;

    };

    void loadModel(const std::string& path, ModelLoadContext& loadContext);

    void loadModelProcessNode(ModelLoadContext& loadContext, aiNode* node, const aiScene* scene);

    void loadModelProcessMesh(ModelLoadContext& loadContext, aiNode* node, unsigned int meshId, aiMesh* mesh, const aiScene* scene);

    class GHOSTGAME_FRAMEWORK_API MeshComponent : public Component
    {
    public:
        std::shared_ptr<Mesh> mesh;

        std::shared_ptr<Shader> shader;

        virtual void update(Engine& engine, Entity& entity, float deltaTime);
    };
}
