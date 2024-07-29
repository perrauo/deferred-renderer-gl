#version 330 core

in vec2 outUv;
in vec3 outNormal;
in vec3 outFragPos;

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;

uniform sampler2D textureDiffuse;

void main()
{
    // The fragment shader writes output to multiple render targets (gPosition, gNormal, gAlbedo).
    gPosition = vec4(outFragPos, 1.0);
    gNormal = vec4(normalize(outNormal), 1.0);
    gAlbedo = texture(textureDiffuse, outUv);
}
