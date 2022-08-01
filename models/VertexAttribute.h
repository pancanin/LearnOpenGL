#pragma once

struct VertexAttribute {
	VertexAttribute(unsigned int id, unsigned int size, unsigned int stride, unsigned int offset) :
		id(id), size(size), stride(stride), offset(offset) {}
	VertexAttribute() {}

	unsigned int id;
	unsigned int size;
	unsigned int stride;
	unsigned int offset;
};
