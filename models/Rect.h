#pragma once

#include "TypeDefs.h"
#include "Object.h"
#include "VertexAttribute.h"

struct Rect : public Object {
	Rect(Point3D origin, float width, float height);

	float* toVertexArray() const override;

	static unsigned int getComponentsCount();
	static std::vector<VertexAttribute> getAttributes();

	Point3D origin;
	float width;
	float height;

	static const unsigned int verticesPerRect = 4;
protected:
	static const unsigned int stride = coordinateComponentsPerVertex + textureCoordsPerVertex;
	static VertexAttribute coordinateAttr;
	static VertexAttribute textureCoordinateAttr;
};
