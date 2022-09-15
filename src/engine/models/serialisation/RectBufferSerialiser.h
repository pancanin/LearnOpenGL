#pragma once

#include "BufferSerialiser.h"

#include "../../../opengl/models/Vertex.h"

class RectBufferSerialiser : public BufferSerialiser {
public:
	float* serialise() const;
	unsigned int size() const;
	unsigned int vertexCount() const;
	unsigned int* indices() const;

	/* For a triangle, the vertex count matches the indices count. */
	unsigned int indicesCount() const;
private:
	const unsigned int verticesPerRect = 4;
	const unsigned int floatsPerRect = (sizeof(Vertex) / sizeof(float)) * verticesPerRect;
	const unsigned int numberOfIndices = 6;
};
