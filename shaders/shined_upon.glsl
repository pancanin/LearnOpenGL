#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
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
in vec2 outTexCoords;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 viewerPos;

void main()
{
vec3 diffuseMap = vec3(texture(material.diffuse, outTexCoords));
  vec3 ambient = diffuseMap * light.ambient;
	vec3 lightDir = normalize(lightPosO - FragWorldPos);
	float dotP = max(dot(normalize(Normal), lightDir), 0.0f);
	
	vec3 diffuse = dotP * diffuseMap * light.diffuse;

	vec3 viewVector = normalize(-FragWorldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(Normal));

	vec3 specularAngleDiff = pow(max(dot(viewVector, reflectDir), 0.0f), material.shininess) * material.specular * light.specular;

  FragColor = vec4(objectColor * (ambient + diffuse + specularAngleDiff), 1.0f);
}