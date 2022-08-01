#pragma once

#include "TypeDefs.h"
#include "Object.h"

struct Rect : public Object {
	Rect(Point3D origin, float width, float height) : origin(origin), width(width), height(height) {}

	float* toVertexArray(unsigned int& size) const {
		float* arr = new float[12];

		arr[0] = origin.x;
		arr[1] = origin.y;
		arr[2] = origin.z;

		arr[3] = origin.x + width;
		arr[4] = origin.y;
		arr[5] = origin.z;

		arr[6] = origin.x + width;
		arr[7] = origin.y + height;
		arr[8] = origin.z;

		arr[9] = origin.x;
		arr[10] = origin.y + height;
		arr[11] = origin.z;

		size = 12;
		return arr;
	}

	Point3D origin;
	float width;
	float height;
};