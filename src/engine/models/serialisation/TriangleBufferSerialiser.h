#pragma once
#include "BufferSerialiser.h"

#include "../../../opengl/models/TriangleVertex.h"

// This class may be a bit too much for the purpose, but it will do for now. A static-time definition of the buffers for the different objects/shapes would be better.
// TODO: Improve name. The idea behind '-Serialiser' is that it 'takes' a Triangle and spits out floats for the buffer. But it does not take a triangle, so...
class TriangleBufferSerialiser :
    public BufferSerialiser
{
public:
	float* serialise() const;
	unsigned int size() const;
	unsigned int vertexCount() const;
	unsigned int* indices() const;

	/* For a triangle, the vertex count matches the indices count. */
	unsigned int indicesCount() const;
private:
	const unsigned int verticesPerTriangle = 3;
	const unsigned int floatsPerTriangle = (sizeof(TriangleVertex) / sizeof(float)) * verticesPerTriangle;
};
