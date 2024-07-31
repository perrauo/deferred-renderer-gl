#version 460 core

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 FragColor;

void main()
{
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedo, TexCoords).rgb;

    // calculate lighting
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));
    vec3 diffuse = max(dot(Normal, lightPos - FragPos), 0.0) * Albedo * lightColor;

    FragColor = vec4(diffuse * lightIntensity * attenuation, 1.0);
}
