#include "Rect.h"

#include "../utils/MathUtils.h"

Rect::Rect(Point3D origin, float width, float height) : origin(origin), width(width), height(height) {}

float* Rect::toVertexArray() const {
	float* arr = new float[getComponentsCount()];

	arr[0] = origin.x;
	arr[1] = origin.y;
	arr[2] = origin.z;

	arr[3] = 0.0f;
	arr[4] = 1.0f;

	arr[5] = origin.x + width;
	arr[6] = origin.y;
	arr[7] = origin.z;

	arr[8] = 1.0f;
	arr[9] = 1.0f;

	arr[10] = origin.x + width;
	arr[11] = origin.y - height;
	arr[12] = origin.z;

	arr[13] = 1.0f;
	arr[14] = 0.0f;

	arr[15] = origin.x;
	arr[16] = origin.y - height;
	arr[17] = origin.z;

	arr[18] = 0.0f;
	arr[19] = 0.0f;

	return arr;
}

unsigned int Rect::getComponentsCount() {
	return verticesPerRect * (coordinateComponentsPerVertex + textureCoordsPerVertex);
}

std::vector<VertexAttribute> Rect::getAttributes() {
	return std::vector<VertexAttribute>{coordinateAttr, textureCoordinateAttr};
}

VertexAttribute Rect::coordinateAttr(0, coordinateComponentsPerVertex, Rect::stride, 0);
VertexAttribute Rect::textureCoordinateAttr(1, Rect::textureCoordsPerVertex, Rect::stride, coordinateComponentsPerVertex);