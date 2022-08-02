#pragma once

#include "TypeDefs.h"

struct Vertex {
	Vertex(Point3D point, Color color) : point(point), color(color) {}

	Point3D point;
	Color color;
};