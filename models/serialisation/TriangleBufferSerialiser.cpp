#include "TriangleBufferSerialiser.h"

float* TriangleBufferSerialiser::serialise() const
{
	return new float[floatsPerTriangle] {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
}

unsigned int TriangleBufferSerialiser::size() const
{
    return floatsPerTriangle;
}
