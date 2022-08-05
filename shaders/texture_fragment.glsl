#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;
in vec4 position;

uniform sampler2D ourAutomaticallyAttachedTexture;

void main()
{
    FragColor = texture(ourAutomaticallyAttachedTexture, TextureCoords) * (position + vec4(1.0, 1.0, 1.0, 1.0f));
}