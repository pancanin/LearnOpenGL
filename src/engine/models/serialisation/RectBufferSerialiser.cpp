#include "RectBufferSerialiser.h"

float* RectBufferSerialiser::serialise() const
{
	// Setting the normals to (0.0f) as we won't use them for now.
	return new float[floatsPerRect] {
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
}

unsigned int RectBufferSerialiser::size() const
{
	return floatsPerRect;
}

unsigned int RectBufferSerialiser::vertexCount() const
{
	return verticesPerRect;
}

unsigned int* RectBufferSerialiser::indices() const
{
	return new unsigned int[] {0,1,3,3,2,1};
}

unsigned int RectBufferSerialiser::indicesCount() const
{
	return numberOfIndices;
}
