#include "framework/mesh.h"
#include "framework/entity.h"
#include "framework/material.h"

#include <vector>
#include <iostream>
#include <memory>

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
        unloadMesh();
    }

    Mesh::Mesh(const std::string& path) {
    }

    void Mesh::draw() const {

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::unloadMesh()
    {
        if (isLoaded)
        {
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
            isLoaded = false;
        }
    }

    void Mesh::loadMesh()
    {
        if (!isLoaded)
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
            isLoaded = true;
        }
    }


    // -------------------
    // MeshComponent
    // -------------------


    void MeshComponent::start(Framework::Engine& engine, Framework::Entity& entity)
    {
        if (mesh)
        {
            // Load mesh if necessary
            mesh->loadMesh();
        }
    }

    void MeshComponent::update(Engine& engine, Entity& entity, float deltaTime)
    {
        if (mesh)
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

            if (material) {
                material->use();
            }

            // Draw the mesh
            mesh->draw();

            // Restore the previous model view matrix
            glPopMatrix();
        }
    }
}