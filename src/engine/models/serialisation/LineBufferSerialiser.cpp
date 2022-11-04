#include "LineBufferSerialiser.h"

float* LineBufferSerialiser::serialise() const
{
	return new float[floatsPerLine] {
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f
	};
}

unsigned int LineBufferSerialiser::size() const
{
	return floatsPerLine;
}

unsigned int LineBufferSerialiser::vertexCount() const
{
	return verticesPerLine;
}

unsigned int* LineBufferSerialiser::indices() const
{
	return new unsigned int[] {0,1};
}

unsigned int LineBufferSerialiser::indicesCount() const
{
	return numberOfIndices;
}
