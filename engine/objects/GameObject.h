#pragma once

#include <memory>

#include "../../models/TypeDefs.h"

struct GameObject {
	GameObject(Point3D position, unsigned int textureUnit) :
		position(position), textureUnit(textureUnit) {}

	Point3D position;
	unsigned int textureUnit;
};