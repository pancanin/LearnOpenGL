#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
	if (texture1) {
		FragColor = texture(texture1, TexCoord);
	} else {
		FragColor = vec4(1.0, 0.5, 0.0, 1.0f);
	}
}