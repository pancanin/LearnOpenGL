#pragma once

#include "BufferSerialiser.h"
#include "../TypeDefs.h"

class PointBufferSerialiser : public BufferSerialiser {
public:
	float* serialise() const;
	unsigned int size() const;
	unsigned int vertexCount() const;
	unsigned int* indices() const;
	unsigned int indicesCount() const;
private:
	const unsigned int verticesCount = 1;
	const unsigned int floatsPerPoint = (sizeof(Point3D) / sizeof(float)) * verticesCount;
	const unsigned int numberOfIndices = 1;
};