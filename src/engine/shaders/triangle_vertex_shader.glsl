#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aIdx;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform vec3 v1pos;
uniform vec3 v2pos;
uniform vec3 v3pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 pos = vec3(1.0f);

	// Todo: check in the book a way to avoid this if-else.
	if (int(aIdx) == 0) {
		pos = v1pos;
	} else if (int(aIdx) == 1) {
		pos = v2pos;
	} else if (int(aIdx) == 2) {
		pos = v3pos;
	}

	FragPos = vec3(model * vec4(pos, 1.0));
  Normal = mat3(transpose(inverse(model))) * aNormal;
  TexCoords = aTexCoords;
    
  gl_Position = projection * view * vec4(FragPos, 1.0);
}