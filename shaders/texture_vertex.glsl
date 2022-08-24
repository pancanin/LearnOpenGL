#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragWorldPos;
out vec3 lightPosO;
out vec3 outColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewerPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
  FragWorldPos = vec3(view * model * vec4(aPos, 1.0));
  Normal = mat3(transpose(inverse(view * model))) * aNormal;
  vec3 lightPosView = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position

	float ambientStrength = 0.2f;
	float specularStr = 0.9f;
	vec3 ambient = objectColor * ambientStrength;
	vec3 lightDir = normalize(lightPosView - FragWorldPos);
	float dotP = max(dot(normalize(Normal), lightDir), 0.0f);
	vec3 diffuse = dotP * lightColor;

	vec3 viewVector = normalize(-FragWorldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(Normal));

	vec3 specularAngleDiff = pow(max(dot(viewVector, reflectDir), 0.0f), 256) * specularStr * lightColor;

  outColor = objectColor * (ambient + diffuse + specularAngleDiff);
}