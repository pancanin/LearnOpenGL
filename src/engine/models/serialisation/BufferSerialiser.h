#pragma once

class BufferSerialiser {
public:
	virtual float* serialise() const = 0;

	/* Size of the buffer. The number of floating point values that are associated with one object. */
	virtual unsigned int size() const = 0;

	virtual unsigned int vertexCount() const = 0;

	/* The order in which vertices should be drawn by the GPU using 'element array buffer'. */
	virtual unsigned int* indices() const = 0;

	virtual unsigned int indicesCount() const = 0;
};
