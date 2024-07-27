#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>

#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace GhostGame::Framework
{    
    class Transform {
    public:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

        Transform() : position(0.0f), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f) {}

        glm::mat4 to_mat4() const {
            glm::mat4 posMatrix = glm::translate(glm::mat4(1.0f), position);
            glm::mat4 rotMatrix = glm::mat4_cast(rotation);
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

            return posMatrix * rotMatrix * scaleMatrix;
        }
    };

}
