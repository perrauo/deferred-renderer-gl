#include "framework/mesh.h"
#include "framework/entity.h"
#include "framework/material.h"
#include "framework/renderer.h"
#include "framework/engine.h"

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
        glEnableVertexAttribArray(0); // Vertices
        glEnableVertexAttribArray(1); // Normals
        glEnableVertexAttribArray(2); // UVs
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);
    }

    void Mesh::unload()
    {
        if (_isLoaded)
        {
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &NBO);
            glDeleteBuffers(1, &UBO);
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

            // UVs
            glGenBuffers(1, &UBO);
            glBindBuffer(GL_ARRAY_BUFFER, UBO);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), &uvs[0], GL_STATIC_DRAW);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
            glEnableVertexAttribArray(2);

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
        using namespace Materials;

        if (
            mesh &&
            geomMaterial
            )
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

            geomMaterial->setUniform(Uniforms::model, entity.transform.getMatrix());
            geomMaterial->setUniform(Uniforms::view, engine.viewMatrix);
            geomMaterial->setUniform(Uniforms::projection, engine.projectionMatrix);
            geomMaterial->setUniform(DeferredShading::Uniforms::gPosition, DeferredShading::Slots::gPosition);
            geomMaterial->setUniform(DeferredShading::Uniforms::gNormal, DeferredShading::Slots::gNormal);
            geomMaterial->setUniform(DeferredShading::Uniforms::gAlbedo, DeferredShading::Slots::gAlbedo);
            geomMaterial->bind(engine);
            
            // Bind the VAO of the mesh and draw it
            // Draw the mesh
            mesh->draw();

            geomMaterial->unbind(engine);

            // Restore the previous model view matrix
            glPopMatrix();
        }
    }

    void MeshComponent::drawLight(Engine& engine, Entity& entity, float deltaTime)
    {
        using namespace Materials;        

        if (
            mesh &&
            lightMaterial
            )
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

            lightMaterial->setUniform(Uniforms::position, entity.transform.position);
            geomMaterial->setUniform(Uniforms::model, entity.transform.getMatrix());
            // TODO: rename light position
            lightMaterial->setUniform(Uniforms::view, engine.viewMatrix);
            lightMaterial->setUniform(Uniforms::projection, engine.projectionMatrix);
            lightMaterial->bind(engine);

            // Draw the quad
            mesh->draw();

            lightMaterial->unbind(engine);

            // Restore the previous model view matrix
            glPopMatrix();
        }
    }

    void MeshComponent::endDrawLight(Engine& engine, Entity& entity, float deltaTime)
    {
    }
}