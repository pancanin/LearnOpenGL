#pragma once
#include "BufferSerialiser.h"

#include "../../../opengl/models/Vertex.h"

// This class may be a bit too much for the purpose, but it will do for now. A static-time definition of the buffers for the different objects/shapes would be better.
// TODO: Improve name. The idea behind '-Serialiser' is that it 'takes' a Triangle and spits out floats for the buffer. But it does not take a triangle, so...
class CubeBufferSerialiser :
	public BufferSerialiser
{
public:
	float* serialise() const;
	unsigned int size() const;
	unsigned int vertexCount() const;
	unsigned int* indices() const;

	unsigned int indicesCount() const;
private:
	const unsigned int verticesPerCube = 3;
	const unsigned int floatsPerCube = (sizeof(Vertex) / sizeof(float)) * verticesPerCube;
	const unsigned int numberOfIndices = 6;
};
