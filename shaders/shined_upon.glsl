#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct DirLight {
	vec3 direction;
	vec3 color;
	vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight {
	vec3 position;
	vec3 color;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct SpotLight {
	vec3 direction;

	vec3 color;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;

uniform DirLight theSun;

#define PL_COUNT 4
uniform PointLight ulichniLampi[PL_COUNT];

uniform SpotLight fenerche;

vec3 CalcDirLight(DirLight light, vec3 normal);  
vec3 CalcPointLight(PointLight light, vec3 normal);

void main()
{
    vec3 result = CalcDirLight(theSun, Normal);

		for (int i = 0; i < 3; i++) {
			result += CalcPointLight(ulichniLampi[i], Normal);
		}

    FragColor = vec4(result, 1.0);
} 

vec3 CalcDirLight(DirLight light, vec3 normal) {
	vec3 ambient = light.ambient * light.color;

	float lightNormalDiff = max(dot(-light.direction, normal), 0.0f);
	vec3 diffuse = lightNormalDiff * light.diffuse * texture(material.diffuse, TexCoords).rgb;

	vec3 viewpoint = normalize(FragPos - viewPos);
	vec3 reflectDir = reflect(light.direction, normal);
	float spec = pow(max(dot(-viewpoint, reflectDir), 0.0f), material.shininess);
	vec3 specular = spec * light.specular * texture(material.specular, TexCoords).rgb;

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal) {
	vec3 ambient = light.ambient * light.color;

	vec3 lightDir = normalize(FragPos - light.position);
	float lightNormalDiff = max(dot(-lightDir, normal), 0.0f);
	vec3 diffuse = lightNormalDiff * light.diffuse * light.color * texture(material.diffuse, TexCoords).rgb;

	vec3 viewpoint = normalize(FragPos - viewPos);
	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(-viewpoint, reflectDir), 0.0f), material.shininess);
	vec3 specular = spec * light.specular * light.color * texture(material.specular, TexCoords).rgb;

	float d = length(light.position - FragPos);
	float atte = 1 / (light.constant + d * light.linear + d * d * light.quadratic);

	return (ambient + diffuse + specular) * atte;
}