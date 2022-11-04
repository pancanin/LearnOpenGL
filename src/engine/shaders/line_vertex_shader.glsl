#version 330 core
layout (location = 0) in vec3 aPos;

in int gl_VertexID;

out vec3 FragPos;
out vec4 Color;

uniform mat4 lineStart;
uniform mat4 direction;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

void main()
{
  Color = color;

	if (0 == gl_VertexID) {
		gl_Position = projection * view * lineStart * vec4(aPos, 1.0);
	} else {
		gl_Position = projection * view * direction * vec4(aPos, 1.0);
	}
}