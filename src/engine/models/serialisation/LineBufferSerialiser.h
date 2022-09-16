#pragma once

#include "BufferSerialiser.h"

#include "../TypeDefs.h"
#include "../../../opengl/models/LineVertex.h"

class LineBufferSerialiser : public BufferSerialiser {
public:
	float* serialise() const;
	float* serialise(Point3D start, Point3D end) const;
	unsigned int size() const;
	unsigned int vertexCount() const;
	unsigned int* indices() const;
	unsigned int indicesCount() const;
private:
	const unsigned int verticesPerLine = 2;
	const unsigned int floatsPerLine = (sizeof(LineVertex) / sizeof(float)) * verticesPerLine;
	const unsigned int numberOfIndices = 2;
};
