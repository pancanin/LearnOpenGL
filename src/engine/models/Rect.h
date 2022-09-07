#pragma once

#include "TypeDefs.h"
struct Rect {
	Rect(Point3D origin, float width, float height);

	Point3D origin;
	float width;
	float height;

	static const unsigned int verticesPerRect;
};
