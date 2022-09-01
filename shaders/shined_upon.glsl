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
    vec3 position; // Used for point light
		vec3 direction; // For directional light we do not compute the light ray from the relative position between object and light
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

		// Attenuation factors
		float constant;
		float linear;
		float quadratic;

		// For spotlight
		float cutoffAngle;
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
	vec3 lightDir = normalize(light.position - FragWorldPos);

	float theta = dot(lightDir, normalize(-light.direction));

	if (theta > light.cutoffAngle) {
		float d = length(FragWorldPos - light.position);
		float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * d * d);

		vec3 diffuseMap = vec3(texture(material.diffuse, outTexCoords));
		vec3 ambient = diffuseMap * light.ambient;

	
		float dotP = max(dot(normalize(Normal), lightDir), 0.0f);
		vec3 diffuse = dotP * diffuseMap * light.diffuse;

		vec3 viewVector = normalize(viewerPos - FragWorldPos);
		vec3 reflectDir = reflect(-lightDir, normalize(Normal));

		vec3 specular = texture(material.specular, outTexCoords).rgb;
		vec3 specularAngleDiff = pow(max(dot(viewVector, reflectDir), 0.0f), material.shininess) * specular * light.specular;

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		FragColor = vec4((ambient + diffuse + specularAngleDiff), 1.0f);
	} else {
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	
}