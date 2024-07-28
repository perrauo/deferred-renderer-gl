#pragma once

#include "framework/api.h"
#include "framework/entity.h"
#include "framework/math.h"

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

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
    class Engine;
    class Mesh;
    class IMaterial;
    class Material;
    class MaterialInstance;
    class Texture;

    struct GHOSTGAME_FRAMEWORK_API ModelLoadMesh
    {
        std::shared_ptr<Mesh> mesh;

        std::shared_ptr<MaterialInstance> material;

        std::shared_ptr<Texture> texture;

        unsigned int materialIdx = -1;

        std::string texturePath;

        Transform transform;
    };

    struct GHOSTGAME_FRAMEWORK_API ModelLoadContext
    {
        std::shared_ptr<Material> baseMaterial;
        std::string baseTexturePath;
        std::unordered_map<unsigned int, ModelLoadMesh> meshes;
        std::unordered_map<unsigned int, std::shared_ptr<MaterialInstance>> materials;
        std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    };

    GHOSTGAME_FRAMEWORK_API void loadModel(const std::string& path, ModelLoadContext& loadContext);
}
