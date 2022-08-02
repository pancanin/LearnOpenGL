#pragma once

#include "TypeDefs.h"
#include "Object.h"

struct Triangle : public Object {
	Triangle(Point3D p1, Point3D p2, Point3D p3) : p1(p1), p2(p2), p3(p3) {}

	virtual float* toVertexArray() const override {
		float* arr = new float[getComponentsCount()];

		arr[0] = p1.x;
		arr[1] = p1.y;
		arr[2] = p1.z;

		arr[3] = p2.x;
		arr[4] = p2.y;
		arr[5] = p2.z;

		arr[6] = p3.x;
		arr[7] = p3.y;
		arr[8] = p3.z;

		return arr;
	}

	virtual unsigned int getComponentsCount() const {
		return 9;
	}

	Point3D p1;
	Point3D p2;
	Point3D p3;

	static const unsigned int verticesPerTriangle = 3;
};
