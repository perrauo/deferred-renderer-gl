#version 330 core

layout (location = 0) in vec2 aPos;

out vec2 outUv;

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0f);
    outUv = (aPos + vec2(1.0f)) / 2.0f; // Transform from range [-1,1] to [0,1]
}