#version 450

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float size;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	gl_PointSize = size;
}