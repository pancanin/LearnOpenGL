#pragma once

#include "TypeDefs.h"

struct Line {
	Line() = default;
	Line(const Vector3D& start, const Vector3D& end, const Color& color) :
		start(start), end(end), color(color) {}

	Vector3D start;
	Vector3D end;
	Color color;
};