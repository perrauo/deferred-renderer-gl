#version 450

layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outPosition;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out vec4 outAlbedo;

uniform sampler2D albedoMap;

void main() {
    outPosition = vec4(fragPosition, 1.0);
    outNormal = vec4(normalize(fragNormal), 1.0);
    outAlbedo = texture(albedoMap, fragTexCoord);
}
