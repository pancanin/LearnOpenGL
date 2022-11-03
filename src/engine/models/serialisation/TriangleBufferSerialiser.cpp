#include "TriangleBufferSerialiser.h"

float* TriangleBufferSerialiser::serialise() const
{
	// Setting the normals to (0.0f) as we won't use them for now.
	return new float[floatsPerTriangle] {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 2.0f
	};
}

unsigned int TriangleBufferSerialiser::size() const
{
    return floatsPerTriangle;
}

unsigned int TriangleBufferSerialiser::vertexCount() const
{
	return verticesPerTriangle;
}

unsigned int* TriangleBufferSerialiser::indices() const
{
	return new unsigned int[]{ 0, 1, 2 };
}

unsigned int TriangleBufferSerialiser::indicesCount() const
{
	return verticesPerTriangle;
}
