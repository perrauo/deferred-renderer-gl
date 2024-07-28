#version 330 core

in vec3 normal;
in vec2 uv;

uniform vec3 materialDiffuse;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform sampler2D textureSampler;

out vec4 fragColor;

void main()
{
    vec3 diffuse = materialDiffuse * max(dot(normal, lightDirection), 0.0);
    vec3 textureColor = texture(textureSampler, uv).rgb;
    fragColor = vec4(diffuse * textureColor * lightColor, 1.0);
}