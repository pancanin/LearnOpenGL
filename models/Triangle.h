#pragma once

#include "TypeDefs.h"
#include "Object.h"
#include "VertexAttribute.h"

struct Triangle : public Object {
	Triangle(Point3D p1, Point3D p2, Point3D p3);

	virtual float* toVertexArray() const override;

	static unsigned int getComponentsCount();

	static std::vector<VertexAttribute> getAttributes();

	Point3D p1;
	Point3D p2;
	Point3D p3;

	static const unsigned int verticesPerTriangle = 3;
	
protected:
	static VertexAttribute coordinateAttr;
};

