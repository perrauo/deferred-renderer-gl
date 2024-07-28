#version 330 core
out vec4 gPosition;
out vec4 gNormal;
out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    gPosition.rgb = FragPos;
    // also store the per-fragment specular intensity in the alpha channel
    gPosition.a = texture(texture_specular1, TexCoords).r;
    
    // store the normal vector in the second gbuffer texture
    gNormal.rgb = normalize(Normal);
    
    // store the diffuse color in the third gbuffer texture
    gAlbedoSpec.rgb = texture(texture_diffuse1, TexCoords).rgb;
    // we're not using specular in this demo, so just set it to 0
    gAlbedoSpec.a = 0.0; 
}
