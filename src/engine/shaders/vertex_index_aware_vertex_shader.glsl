#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

in int gl_VertexID;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform vec3 v1pos;
uniform vec3 v2pos;
uniform vec3 v3pos;
uniform vec3 v4pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float textureScale;

void main()
{
	vec3 pos = vec3(1.0f);

	if (gl_VertexID == 0) {
		pos = v1pos;
	} else if (gl_VertexID == 1) {
		pos = v2pos;
	} else if (gl_VertexID == 2) {
		pos = v3pos;
	} else if (gl_VertexID == 3) {
		pos = v4pos;
	}

	FragPos = vec3(model * vec4(pos, 1.0));
  Normal = mat3(transpose(inverse(model))) * aNormal;
  TexCoords = aTexCoords * textureScale;
    
  gl_Position = projection * view * vec4(FragPos, 1.0);
}