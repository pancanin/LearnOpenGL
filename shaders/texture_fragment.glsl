#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;
in vec4 position;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend;

void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}