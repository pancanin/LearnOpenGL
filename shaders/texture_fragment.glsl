#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int isMouseInsideTriangle;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

	if (isMouseInsideTriangle == 0) {
		FragColor = vec4(0.5, 0.3, 0.0, 1.0f);
	} else {
		FragColor = vec4(0.0, 0.7, 0.1, 1.0f);
	}
	
}