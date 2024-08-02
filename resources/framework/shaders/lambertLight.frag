#version 460 core

layout(location = 1) in vec2 fragUv;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 outColor;

void main()
{
    // retrieve data from gbuffer
    vec3 fragPos = texture(gPosition, fragUv).rgb;
    vec3 normal = texture(gNormal, fragUv).rgb;
    vec3 albedo = texture(gAlbedo, fragUv).rgb;

    // calculate lighting
    float dist = length(lightPos - fragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * (dist * dist));
    vec3 diffuse = max(dot(normal, normalize(lightPos - fragPos)), 0.0) * albedo * lightColor;

    outColor = vec4(diffuse * lightIntensity * attenuation, 1.0);
}