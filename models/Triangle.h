#pragma once

#include "TypeDefs.h"
#include "Object.h"

struct Triangle : public Object {
	Triangle(Point3D p1, Point3D p2, Point3D p3) : p1(p1), p2(p2), p3(p3) {}

	float* toVertexArray(int& outSize) const override {
		float* arr = new float[9];

		arr[0] = p1.x;
		arr[1] = p1.y;
		arr[2] = p1.z;

		arr[3] = p2.x;
		arr[4] = p2.y;
		arr[5] = p2.z;

		arr[6] = p3.x;
		arr[7] = p3.y;
		arr[8] = p3.z;

		outSize = 9;
		return arr;
	}

	Point3D p1;
	Point3D p2;
	Point3D p3;
};
