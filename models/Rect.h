#pragma once

#include "TypeDefs.h"
#include "Object.h"

struct Rect : public Object {
	Rect(Point3D origin, float width, float height);

	Point3D origin;
	float width;
	float height;

	static const unsigned int verticesPerRect;
};
