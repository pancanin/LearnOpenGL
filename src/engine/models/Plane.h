#pragma once

#include "TypeDefs.h"

struct Plane {
	Plane() = default;
	Plane(const Vector3D& point, const Vector3D& normal, const Color& color) :
		point(point), normal(normal), color(color) {}

	Vector3D point;
	Vector3D normal;
	Color color;
};
