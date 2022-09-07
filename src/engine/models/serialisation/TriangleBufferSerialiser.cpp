#include "TriangleBufferSerialiser.h"

float* TriangleBufferSerialiser::serialise() const
{
	// Setting the normals to (0.0f) as we won't use them for now.
	return new float[floatsPerTriangle] {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f
	};
}

unsigned int TriangleBufferSerialiser::size() const
{
    return floatsPerTriangle;
}
