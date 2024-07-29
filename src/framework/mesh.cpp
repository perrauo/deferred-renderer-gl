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
        unload();
    }

    Mesh::Mesh(const std::string& path) {
    }

    void Mesh::draw() const {

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::unload()
    {
        if (_isLoaded)
        {
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &NBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
            _isLoaded = false;
        }
    }

    void Mesh::load()
    {
        if (!_isLoaded)
        {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // Vertices
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
            glEnableVertexAttribArray(0);

            // Normals
            glGenBuffers(1, &NBO);
            glBindBuffer(GL_ARRAY_BUFFER, NBO);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
            glEnableVertexAttribArray(1);

            // Indices
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

            glBindVertexArray(0); // Unbind VAO
            _isLoaded = true;
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
            mesh->load();
        }
    }

    void MeshComponent::update(Engine& engine, Entity& entity, float deltaTime)
    {
    }

    void MeshComponent::draw(Engine& engine, Entity& entity, float deltaTime)
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

            // Bind the VAO of the mesh and draw it
            // Draw the mesh
            mesh->draw();


            // Restore the previous model view matrix
            glPopMatrix();
        }
    }
}