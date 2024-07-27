#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>

#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

struct aiNode;
struct aiScene;
struct aiMesh;

namespace GhostGame::Framework
{
    class Model {
    public:
        // Constructor
        Model(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
        Model(const std::string& path); // New constructor for loading .dae files

        // Render the model
        void draw() const;

        // Load model from file
        void loadModel(const std::string& path);

    private:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        GLuint VAO, VBO, EBO;

        // Initialize the model
        void initModel();

        // Process a node in the scene
        void processNode(aiNode* node, const aiScene* scene);

        // Process a mesh in the scene
        void processMesh(aiMesh* mesh, const aiScene* scene);
    };
}
