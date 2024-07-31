#version 460 core

in vec2 outUv;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform vec3 position;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 FragColor;

void main()
{
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, outUv).rgb;
    vec3 Normal = texture(gNormal, outUv).rgb;
    vec3 Albedo = texture(gAlbedo, outUv).rgb;

    // calculate lighting
    float dist = length(position - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * (dist * dist));
    vec3 diffuse = max(dot(Normal, normalize(position - FragPos)), 0.0) * Albedo * lightColor;

    FragColor = vec4(diffuse * lightIntensity * attenuation, 1.0);
}