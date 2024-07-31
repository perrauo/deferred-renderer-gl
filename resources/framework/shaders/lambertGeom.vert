#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;

out vec2 outUv;
out vec3 outNormal;
out vec3 outFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    outFragPos = vec3(model * vec4(aPos, 1.0));
    outNormal = mat3(transpose(inverse(model))) * aNormal;  
    outUv = aUv;
    
    gl_Position = projection * view * vec4(aPos, 1.0);
}
