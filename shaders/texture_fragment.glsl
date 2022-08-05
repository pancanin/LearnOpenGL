#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;
in vec4 position;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend;

void main()
{
    FragColor = mix(texture(texture1, TextureCoords), texture(texture2, vec2(-TextureCoords.x, TextureCoords.y)), blend);
}