#pragma once

#include <vector>

#include "VertexAttribute.h"

class Object {
public:
	virtual float* toVertexArray() const = 0;
protected:
	static const unsigned int textureCoordsPerVertex = 2;
	static const unsigned int coordinateComponentsPerVertex = 3;
};