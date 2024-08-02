#version 460 core

layout (location = 3) in vec2 fragUv;
layout (location = 4) in vec3 fragNormal;
layout (location = 5) in vec3 fragPosition;

// These layout indices correspond to the attachment points in your framebuffer. 
// When you create your framebuffer, you specify the attachments using glDrawBuffers:
// GLenum attachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
// glDrawBuffers(3, attachments);
layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;

uniform sampler2D textureDiffuse;

void main()
{
    // The fragment shader writes output to multiple render targets (gPosition, gNormal, gAlbedo).
    gPosition = vec4(fragPosition, 1.0);
    gNormal = vec4(normalize(fragNormal), 1.0);
    gAlbedo = texture(textureDiffuse, fragUv);
}
