#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;

uniform sampler2D ourAutomaticallyAttachedTexture;

void main()
{
    FragColor = texture(ourAutomaticallyAttachedTexture, TextureCoords);
}