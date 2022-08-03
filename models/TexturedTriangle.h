#pragma once

#include "TypeDefs.h"
#include "Triangle.h"

struct TexturedTriangle : Triangle
{
	TexturedTriangle(Point3D p1, TextureCoordinate t1,
		Point3D p2, TextureCoordinate t2,
		Point3D p3, TextureCoordinate t3) : Triangle(p1, p2, p3), t1(t1), t2(t2), t3(t3) {}

	virtual float* toVertexArray() const override {
		float* arr = new float[getComponentsCount()];

		arr[0] = p1.x;
		arr[1] = p1.y;
		arr[2] = p1.z;

		arr[3] = t1.x;
		arr[4] = t1.y;

		arr[5] = p2.x;
		arr[6] = p2.y;
		arr[7] = p2.z;

		arr[8] = t2.x;
		arr[9] = t2.y;

		arr[10] = p3.x;
		arr[11] = p3.y;
		arr[12] = p3.z;

		arr[13] = t3.x;
		arr[14] = t3.y;

		return arr;
	}

	virtual unsigned int getComponentsCount() const {
		return Triangle::getComponentsCount() + (textureComponentsPerVertex * Triangle::verticesPerTriangle);
	}

	TextureCoordinate t1;
	TextureCoordinate t2;
	TextureCoordinate t3;

	static const unsigned int textureComponentsPerVertex = 2;
};