#pragma once

#include "TypeDefs.h"
#include "ObjectType.h"

struct Object {
	glm::vec3 position;
	glm::vec3 rotationAxis;
	glm::vec3 velocity;
	ObjectType type;
	unsigned int textureUnit;
	float rotationAngle = 0.0f;
};