#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;
in float myTextureId;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	if (myTextureId == 0) {
		FragColor = texture(texture0, TextureCoords);
	} else if (myTextureId == 1) {
		FragColor = texture(texture1, TextureCoords);
	}
    
}