#pragma once

class VertexBufferObject {
public:
	void init();
	void bind();
	void fillBuffer(float* data, int size);

	~VertexBufferObject();
private:
	unsigned int id;
};