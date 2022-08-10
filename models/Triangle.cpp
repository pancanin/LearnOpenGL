#include "Triangle.h"

Triangle::Triangle(Point3D p1, Point3D p2, Point3D p3) : p1(p1), p2(p2), p3(p3) {}

float* Triangle::toVertexArray() const {
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

unsigned int Triangle::getComponentsCount() {
	return verticesPerTriangle;
}

std::vector<VertexAttribute> Triangle::getAttributes() {
	return std::vector<VertexAttribute>{coordinateAttr};
}

VertexAttribute Triangle::coordinateAttr(0, 3, 3, 0);