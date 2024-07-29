#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos; // add this

out vec3 FragPos; // add this

void main()
{
    vec4 pos = model * vec4(aPos, 1.0);
    gl_Position = projection * view * pos;
    FragPos = vec3(model * vec4(aPos, 1.0)); // add this
}
