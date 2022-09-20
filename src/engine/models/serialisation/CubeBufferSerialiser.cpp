#include "CubeBufferSerialiser.h"

// TODO: Improve texturing in the case of reused vertices (EBO)
float* CubeBufferSerialiser::serialise() const
{
	return new float[floatsPerCube] {
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // A
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // B
			1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // C
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // D
			-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // E
			1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // F
			1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // G
			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f // H
	};
}

unsigned int CubeBufferSerialiser::size() const
{
	return floatsPerCube;
}

unsigned int CubeBufferSerialiser::vertexCount() const
{
	return verticesPerCube;
}

unsigned int* CubeBufferSerialiser::indices() const
{
	return new unsigned int[numberOfIndices] {
		0,1,3,
			3,2,1,
			1,2,6,
			6,5,1,
			7,6,5,
			5,4,7,
			0,4,7,
			7,3,0,
			0,4,5,
			5,1,0,
			3,2,6,
			6,7,3
	};
}

unsigned int CubeBufferSerialiser::indicesCount() const
{
	return numberOfIndices;
}
