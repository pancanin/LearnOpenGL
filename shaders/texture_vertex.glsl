#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoords;

out vec2 TextureCoords;
out vec4 position;

void main()
{
    gl_Position = vec4(aPos, 1.0);
		TextureCoords = aTextureCoords;
		position = gl_Position;
}
