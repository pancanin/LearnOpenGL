#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;
in float myTextureId;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	if (int(myTextureId) == 1) {
		FragColor = texture(texture1, TextureCoords);
	} else if (int(myTextureId) == 2) {
		FragColor = texture(texture2, TextureCoords);
	}
}