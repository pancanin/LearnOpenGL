#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
		sampler2D emissive;
    float shininess;
}; 
  
uniform Material material;

struct Light {
    //vec3 position;
		vec3 direction; // For directional light we do not compute the light ray from the relative position between object and light
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
	vec3 lightDir = normalize(-light.direction);
	float dotP = max(dot(normalize(Normal), lightDir), 0.0f);
	
	vec3 diffuse = dotP * diffuseMap * light.diffuse;

	vec3 viewVector = normalize(-FragWorldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(Normal));

	vec3 specular = vec3(1.0f) - texture(material.specular, outTexCoords).rgb;
	vec3 specularAngleDiff = pow(max(dot(viewVector, reflectDir), 0.0f), material.shininess) * specular * light.specular;

	vec3 emissive = texture(material.emissive, outTexCoords).rgb;
  FragColor = vec4((ambient + diffuse + specularAngleDiff), 1.0f);
}