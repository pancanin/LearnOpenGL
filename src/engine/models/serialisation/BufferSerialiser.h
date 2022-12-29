#pragma once

#include <vector>

#include "../../../opengl/models/VertexAttribute.h"
#include "../../../opengl/models/Vertex.h"

class BufferSerialiser {
public:
	virtual float* serialise() const = 0;

	/* Size of the buffer. The number of floating point values that are associated with one object. */
	virtual unsigned int size() const = 0;

	virtual unsigned int vertexCount() const = 0;

	/* The order in which vertices should be drawn by the GPU using 'element array buffer'. */
	virtual unsigned int* indices() const = 0;

	virtual unsigned int indicesCount() const = 0;

	virtual std::vector<VertexAttribute> attributes() const {
		return {
			VertexAttribute{ 0, sizeof(Vertex::position) / sizeof(float), sizeof(Vertex) / sizeof(float), 0 },
			VertexAttribute{ 1, sizeof(Vertex::normal) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::normal) / sizeof(float) },
			VertexAttribute{ 2, sizeof(Vertex::textureCoords) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::textureCoords) / sizeof(float) }
		};
	}
};
