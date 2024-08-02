#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (location = 3) out vec2 fragUv;
layout (location = 4) out vec3 fragNormal;
layout (location = 5) out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D diffuseTexture;


void main()
{
    fragPos = vec3(model * vec4(position, 1.0));
    fragNormal = mat3(transpose(inverse(model))) * normal;  
    fragUv = uv;
    
    gl_Position = projection * view * vec4(position, 1.0);
}
