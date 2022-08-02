#version 330 core
layout (location = 0) in vec3 aPos;

uniform float offset;
out vec4 positionColor;

void main()
{
    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
		positionColor = gl_Position;
}
