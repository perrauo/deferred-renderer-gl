#include "framework/mesh.h"
#include "framework/entity.h"
#include "framework/shader.h"

#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GL/glew.h"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace GhostGame::Framework
{
    // -------------------
    // Mesh
    // -------------------


    Mesh::Mesh() {
    }

    Mesh::~Mesh() {}

    Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
        : vertices(vertices), indices(indices) {
        initModel();
    }

    Mesh::Mesh(const std::string& path) {
        loadModel(path);
        initModel();
    }

    void Mesh::draw() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::initModel()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }


    void loadModel(const std::string& path, ModelLoadContext& loadContext)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        loadModelProcessNode(loadContext, scene->mRootNode, scene);
    }

    void loadModelProcessNode(ModelLoadContext& loadContext, aiNode* node, const aiScene* scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            loadModelProcessMesh(loadContext, node, i, mesh, scene);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            loadModelProcessNode(loadContext, node->mChildren[i], scene);
        }
    }

    void loadModelProcessMesh(ModelLoadContext& loadContext, aiNode* node, unsigned int meshId, aiMesh* mesh, const aiScene* scene)
    {   
        auto md = node->mMetaData;
        //node->mTransformation
        //loadContext.results.emplace(mesh.i)
        auto& result = loadResults.emplace_back();
        result.mesh = std::make_unique<Mesh>();
        result.materialIdx = mesh->mMaterialIndex;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            result.mesh->vertices.push_back(mesh->mVertices[i].x);
            result.mesh->vertices.push_back(mesh->mVertices[i].y);
            result.mesh->vertices.push_back(mesh->mVertices[i].z);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                result.mesh->indices.push_back(face.mIndices[j]);
        }
    }



    // -------------------
    // MeshComponent
    // -------------------

    void MeshComponent::update(Engine& engine, Entity& entity, float deltaTime)
    {
        // Get the transformation matrix from the entity
        glm::mat4 transform = entity.transform.getMatrix();

        // Convert the transformation matrix to a format that OpenGL can use
        GLfloat glTransform[16];
        const float* transformData = glm::value_ptr(transform);
        std::copy(transformData, transformData + 16, glTransform);

        // Apply the transformation
        glPushMatrix();
        glMultMatrixf(glTransform);

        if (shader) {
            shader->use();
        }

        // Draw the mesh
        mesh->draw();

        // Restore the previous model view matrix
        glPopMatrix();
    }
}