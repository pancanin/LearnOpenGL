#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;
in vec4 position;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TextureCoords), texture(texture2, TextureCoords), 0.2);
}