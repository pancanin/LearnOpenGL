#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragWorldPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewerPos;

void main()
{
		float ambientStrength = 0.2f;
		float specularStr = 0.9f;
		vec3 ambient = objectColor * ambientStrength;
		vec3 lightDir = normalize(lightPos - FragWorldPos);
		float dotP = max(dot(lightDir, Normal), 0.0f);
		vec3 diffuse = dotP * lightColor;

		vec3 viewVector = normalize(viewerPos - FragWorldPos);
		vec3 reflectDir = reflect(-lightDir, Normal);

		vec3 specularAngleDiff = pow(max(dot(viewVector, reflectDir), 0.0f), 32) * specularStr * lightColor;

    FragColor = vec4(objectColor * (ambient + diffuse + specularAngleDiff), 1.0f);
}