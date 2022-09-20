#pragma once

#include "TypeDefs.h"
#include "ObjectType.h"

struct Object {
	glm::vec3 position;
	glm::vec3 rotationAxis;
	glm::vec3 velocity;
	glm::vec3 scaleFactor = glm::vec3(1.0f);
	ObjectType type;
	unsigned int textureUnit;
	float rotationAngle = 0.0f;
	bool intersectible = true;
};