#include "PointBufferSerialiser.h"

float* PointBufferSerialiser::serialise() const
{
	return new float[] {
		0.0f, 0.0f, 0.0f // position
	};
}

unsigned int PointBufferSerialiser::size() const
{
	return floatsPerPoint;
}

unsigned int PointBufferSerialiser::vertexCount() const
{
	return verticesCount;
}

unsigned int* PointBufferSerialiser::indices() const
{
	return new unsigned int[] { 0 };
}

unsigned int PointBufferSerialiser::indicesCount() const
{
	return numberOfIndices;
}
