#version 460 core

layout (location = 0) in vec2 position;
layout(location = 1) out vec2 fragUv;

void main()
{
    gl_Position = vec4(position, 0.0f, 1.0f);
    fragUv = (position + vec2(1.0f)) / 2.0f; // Transform from range [-1,1] to [0,1]
}