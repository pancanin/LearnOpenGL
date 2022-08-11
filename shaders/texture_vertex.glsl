#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoords;
layout (location = 2) in float aTextureId;

out vec2 TextureCoords;
out float myTextureId;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
		TextureCoords = aTextureCoords;
		myTextureId = aTextureId;
}
