#pragma once

#include "TypeDefs.h"
#include "ObjectType.h"

struct Object {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 velocity;
	ObjectType type;
};