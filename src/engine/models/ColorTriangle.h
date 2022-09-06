#pragma once

#include "Triangle.h"
#include "Vertex.h"
#include "TypeDefs.h"

struct ColorTriangle : Triangle {
	ColorTriangle(Vertex v1, Vertex v2, Vertex v3) :
		Triangle(v1.point, v2.point, v3.point), v1Color(v1.color), v2Color(v2.color), v3Color(v3.color) {}

	virtual float* toVertexArray() const override {
		float* arr = new float[getComponentsCount()];

		arr[0] = p1.x;
		arr[1] = p1.y;
		arr[2] = p1.z;

		arr[3] = v1Color.r;
		arr[4] = v1Color.g;
		arr[5] = v1Color.b;
		arr[6] = v1Color.a;

		arr[7] = p2.x;
		arr[8] = p2.y;
		arr[9] = p2.z;

		arr[10] = v2Color.r;
		arr[11] = v2Color.g;
		arr[12] = v2Color.b;
		arr[13] = v2Color.a;

		arr[14] = p3.x;
		arr[15] = p3.y;
		arr[16] = p3.z;

		arr[17] = v3Color.r;
		arr[18] = v3Color.g;
		arr[19] = v3Color.b;
		arr[20] = v3Color.a;

		return arr;
	}

	virtual unsigned int getComponentsCount() const {
		return Triangle::getComponentsCount() + (colorComponentsPerVertex * Triangle::verticesPerTriangle);
	}

	static const unsigned int colorComponentsPerVertex = 4;

	Color v1Color;
	Color v2Color;
	Color v3Color;
};