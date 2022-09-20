#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in float isEnd;

out vec3 FragPos;
out vec4 Color;

uniform mat4 lineStart;
uniform mat4 lineEnd;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  Color = aColor;

	if (0 == int(isEnd)) {
		gl_Position = projection * view * vec4(vec3(lineStart * vec4(aPos, 1.0)), 1.0);
	} else {
		gl_Position = projection * view * vec4(vec3(lineEnd * vec4(aPos, 1.0)), 1.0);
	}
}