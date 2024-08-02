#version 460 core

layout(location = 2) in vec2 fragUv;

out vec4 outColor;

uniform sampler2D screenTexture;

void main()
{
    outColor = texture(screenTexture, fragUv);
}