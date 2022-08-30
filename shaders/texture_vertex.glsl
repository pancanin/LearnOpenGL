#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FragWorldPos;
out vec3 lightPosO;
out vec2 outTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
  FragWorldPos = vec3(view * model * vec4(aPos, 1.0));
  Normal = mat3(transpose(inverse(view * model))) * aNormal;
  lightPosO = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
	outTexCoords = aTexCoords;
}