#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D dtexture;

void main()
{
	FragColor = texture(dtexture, TexCoords);
}