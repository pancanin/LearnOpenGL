#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;
in vec4 position;
in float outTextureId;

uniform sampler2D texture0;

void main()
{
    FragColor = texture(texture0, TextureCoords);
}