#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 lightPos; // add this

in vec3 FragPos; // add this

void main()
{
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance)); // adjust these values as needed

    vec3 color = lightColor * lightIntensity * attenuation;
    FragColor = vec4(color, 1.0);
}