#include "framework/model.h"
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


namespace GhostGame::Framework
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

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                result.mesh->indices.push_back(face.mIndices[j]);
        }

    }

    void loadModelProcessMaterial(ModelLoadContext& loadContext, const aiScene* scene, const aiNode* node, unsigned int materialId)
    {       
        auto material = std::make_shared<MaterialInstance>(loadContext.baseMaterial);
        loadContext.materials[materialId] = material;        
        aiMaterial* aiMaterial = scene->mMaterials[materialId];
        aiString aiTexturePath;
        std::shared_ptr<Texture> texture = nullptr;
        if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexturePath) == AI_SUCCESS)
        {
            std::string texturePath = RES(loadContext.baseTexturePath + "/" + aiTexturePath.C_Str());
            auto it = loadContext.textures.find(texturePath);
            if (it == loadContext.textures.end())
            {
                texture = std::make_shared<Texture>(texturePath);
                loadContext.textures[texturePath] = texture;
            }
            else
            {
                texture = it->second;
            }
        }
        if (texture)
        {
            if (material->getName() == Materials::Lambert::name)
            {
                material->setUniform(Materials::Lambert::Uniforms::textureSampler, texture);
            }
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
            if (loadContext.materials.find(materialIdx) != loadContext.materials.end())
            {
                mesh.material = loadContext.materials[materialIdx];
            }
        }
    }
}