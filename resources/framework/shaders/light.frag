#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform sampler2D gPosition;
layout(set = 0, binding = 1) uniform sampler2D gNormal;
layout(set = 0, binding = 2) uniform sampler2D gAlbedo;
layout(set = 0, binding = 3) uniform sampler2D gMaterial;

uniform vec3 lightPosition;
uniform vec3 lightColor;


vec3 phongLighting(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightCol) {
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = lightCol * spec;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightCol * diff;
    return (diffuse + specular);
}

vec3 lambertLighting(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightCol) {
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    return lightCol * diff;
}

void main() {
    vec3 fragPos = texture(gPosition, gl_FragCoord.xy / vec2(textureSize(gPosition, 0))).rgb;
    vec3 normal = texture(gNormal, gl_FragCoord.xy / vec2(textureSize(gNormal, 0))).rgb;
    vec3 albedo = texture(gAlbedo, gl_FragCoord.xy / vec2(textureSize(gAlbedo, 0))).rgb;
    int material = int(texture(gMaterial, gl_FragCoord.xy / vec2(textureSize(gMaterial, 0))).r);

    vec3 result;
    if (material == 0) {
        result = phongLighting(normal, fragPos, lightPosition, lightColor);
    } else {
        result = lambertLighting(normal, fragPos, lightPosition, lightColor);
    }

    outColor = vec4(result * albedo, 1.0);
}
