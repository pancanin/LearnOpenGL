#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
in vec3 Normal;
in vec3 FragWorldPos;
in vec3 lightPosO;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 viewerPos;

void main()
{
  vec3 ambient = objectColor * material.ambient * light.ambient;
	vec3 lightDir = normalize(lightPosO - FragWorldPos);
	float dotP = max(dot(normalize(Normal), lightDir), 0.0f);
	vec3 diffuse = dotP * lightColor * material.diffuse * light.diffuse;

	vec3 viewVector = normalize(-FragWorldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(Normal));

	vec3 specularAngleDiff = pow(max(dot(viewVector, reflectDir), 0.0f), material.shininess) * material.specular * light.specular;

  //FragColor = objectColor * (ambient + diffuse + specularAngleDiff);
	FragColor = vec3(1.0f);
}