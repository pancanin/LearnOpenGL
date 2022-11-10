#pragma once

#include "TypeDefs.h"

// TODO: Rename this to Ray
struct Line {
	Line() = default;
	Line(const Vector3D& start, const Vector3D& direction, const Color& color) :
		start(start), direction(direction), color(color) {}

	Vector3D start;
	Vector3D direction;
	Color color;
};