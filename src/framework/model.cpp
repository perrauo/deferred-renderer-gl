#include "framework/model.h"
#include "framework/engine.h"
#include "framework/entity.h"
#include "framework/material.h"
#include "framework/mesh.h"
#include "framework/texture.h"

#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GL/glew.h"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Experiment::Framework
{
    // -------------------
    // Model
    // -------------------

    Transform convertTransform(const aiMatrix4x4& m)
    {
        Transform transform;
        aiMatrix4x4 temp = m; // Create a copy of m

        // Extract the translation
        transform.position = glm::vec3(temp.a4, temp.b4, temp.c4);

        // Extract the scale
        glm::vec3 scale;
        scale.x = glm::length(glm::vec3(temp.a1, temp.b1, temp.c1));
        scale.y = glm::length(glm::vec3(temp.a2, temp.b2, temp.c2));
        scale.z = glm::length(glm::vec3(temp.a3, temp.b3, temp.c3));
        transform.scale = scale;

        // Remove the scale from the matrix
        temp.a1 /= scale.x; temp.b1 /= scale.x; temp.c1 /= scale.x;
        temp.a2 /= scale.y; temp.b2 /= scale.y; temp.c2 /= scale.y;
        temp.a3 /= scale.z; temp.b3 /= scale.z; temp.c3 /= scale.z;

        // Extract the rotation quaternion
        glm::mat4 rotationMat(
            temp.a1, temp.b1, temp.c1, 0.0f,
            temp.a2, temp.b2, temp.c2, 0.0f,
            temp.a3, temp.b3, temp.c3, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
        transform.rotation = glm::quat_cast(rotationMat);

        return transform;
    }


    void loadModelProcessMesh(ModelLoadContext& loadContext, const aiScene* scene, const aiNode* node, unsigned int meshId)
    {
        auto mesh = scene->mMeshes[node->mMeshes[meshId]];
        auto& result = loadContext.meshes[meshId];
        result.mesh = std::make_unique<Mesh>();
        result.materialIdx = mesh->mMaterialIndex;
        result.transform = convertTransform(node->mTransformation);

        // Check if the material has a texture
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            result.mesh->vertices.push_back(mesh->mVertices[i].x);
            result.mesh->vertices.push_back(mesh->mVertices[i].y);
            result.mesh->vertices.push_back(mesh->mVertices[i].z);
        }

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            result.mesh->normals.push_back(mesh->mNormals[i].x);
            result.mesh->normals.push_back(mesh->mNormals[i].y);
            result.mesh->normals.push_back(mesh->mNormals[i].z);
        }

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            // TODO: multiple uv sets. For now assume a single uv set.
            // mesh->mNumUVComponents is this it?
            if (mesh->mTextureCoords[0]) // Check if texture coordinates exist
            {
                result.mesh->uvs.push_back(mesh->mTextureCoords[0][i].x);
                result.mesh->uvs.push_back(mesh->mTextureCoords[0][i].y);
            }
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                result.mesh->indices.push_back(face.mIndices[j]);
        }

    }

    std::shared_ptr<Texture> doLoadTexture(ModelLoadContext& loadContext, const aiString& aiTexturePath)
    {
        std::string texturePath = RES(loadContext.baseTexturePath + "/" + aiTexturePath.C_Str());
        auto it = loadContext.textures.find(texturePath);
        if (it == loadContext.textures.end())
        {
            auto texture = std::make_shared<Texture>(texturePath);
            loadContext.textures[texturePath] = texture;
            return texture;
        }
        else
        {
            return it->second;
        }
    }

    void loadModelProcessMaterial(ModelLoadContext& loadContext, const aiScene* scene, const aiNode* node, unsigned int materialId)
    {       
        auto& loadMaterial = loadContext.materials[materialId];
        loadMaterial.material = std::make_shared<MaterialProxy>(loadContext.materialType);
      
        aiMaterial* aiMaterial = scene->mMaterials[materialId];
        aiString aiTexturePath;
        std::shared_ptr<Texture> texture = nullptr;

        if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexturePath) == AI_SUCCESS)
        {
            texture = doLoadTexture(loadContext, aiTexturePath);
            loadMaterial.material->setUniform(Materials::Uniforms::albedoMap, texture);
        }
        if (aiMaterial->GetTexture(aiTextureType_SHININESS, 0, &aiTexturePath) == AI_SUCCESS)
        {
            texture = doLoadTexture(loadContext, aiTexturePath);
            loadMaterial.material->setUniform(Materials::Uniforms::specularMap, texture);
        }
        if (aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &aiTexturePath) == AI_SUCCESS)
        {
            texture = doLoadTexture(loadContext, aiTexturePath);
            loadMaterial.material->setUniform(Materials::Uniforms::normalMap, texture);
        }

        if (loadMaterial.material->type == MaterialType::Lambert)
        {
            auto& engine = loadContext.engine;
            auto lambert = engine.config.at("Lambert").as_object();

            float lightIntensity = lambert.at("lightIntensity").as_double();
            loadMaterial.material->setUniform(Materials::Lambert::Uniforms::lightIntensity, lightIntensity);

            auto lightColor = lambert.at("lightColor").as_object();
            glm::vec3 color;
            color.r = lightColor.at("r").as_double();
            color.g = lightColor.at("g").as_double();
            color.b = lightColor.at("b").as_double();
            loadMaterial.material->setUniform(Materials::Lambert::Uniforms::lightColor, color);

            auto diffuseColor = lambert.at("diffuseColor").as_object();
            color.r = diffuseColor.at("r").as_double();
            color.g = diffuseColor.at("g").as_double();
            color.b = diffuseColor.at("b").as_double();
            loadMaterial.material->setUniform(Materials::Lambert::Uniforms::diffuseColor, color);
        }
    }

    void loadModelProcessNode(ModelLoadContext& loadContext, const aiScene* scene, const aiNode* node)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            loadModelProcessMesh(loadContext, scene, node, i);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            loadModelProcessNode(loadContext, scene, node->mChildren[i]);
        }
    }

    void loadModel(const std::string& path, ModelLoadContext& loadContext)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        for (int i = 0; i < scene->mNumMaterials; i++)
        {
            loadModelProcessMaterial(loadContext, scene, scene->mRootNode, i);
        }

        loadModelProcessNode(loadContext, scene, scene->mRootNode);

        // Reuse existing shaders and textures
        for (auto& [_, mesh] : loadContext.meshes)
        {
            int materialIdx = mesh.materialIdx;
            auto it = loadContext.materials.find(materialIdx);
            if (it != loadContext.materials.end())
            {
                mesh.material = it->second.material;
            }
        }
    }
}