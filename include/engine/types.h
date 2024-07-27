#ifndef GHOSTGAME_TYPES_H
#define GHOSTGAME_TYPES_H

#include <GL/glew.h>
#include <vector>

namespace GhostGame
{
    class Model {
    public:
        // Constructor
        Model(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);

        // Render the model
        void render() const;

    private:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        GLuint VAO, VBO, EBO;

        // Initialize the model
        void initModel();
    };

    class Transform {
    public:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

        Transform() : position(0.0f), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f) {}

        glm::mat4 to_mat4() const {
            glm::mat4 posMatrix = glm::translate(position);
            glm::mat4 rotMatrix = glm::mat4_cast(rotation);
            glm::mat4 scaleMatrix = glm::scale(scale);

            return posMatrix * rotMatrix * scaleMatrix;
        }
    };

}

#endif