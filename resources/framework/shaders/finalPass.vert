#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

layout(location = 2) out vec2  fragUv;

void main()
{
    gl_Position = vec4(position, 1.0);
    fragUv = uv;
}
