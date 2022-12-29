#pragma once

#include <vector>

#include "BufferSerialiser.h"

#include "../TypeDefs.h"
#include "../../../opengl/models/LineVertex.h"

class LineBufferSerialiser : public BufferSerialiser {
public:
	float* serialise() const;
	unsigned int size() const;
	unsigned int vertexCount() const;
	unsigned int* indices() const;
	unsigned int indicesCount() const;
	std::vector<VertexAttribute> attributes() const;
private:
	const unsigned int verticesPerLine = 2;
	const unsigned int floatsPerLine = (sizeof(LineVertex) / sizeof(float)) * verticesPerLine;
	const unsigned int numberOfIndices = 2;
};
