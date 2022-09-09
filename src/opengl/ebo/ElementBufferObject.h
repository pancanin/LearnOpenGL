#pragma once

class ElementBufferObject {
public:
	void init();
	void bind();
	void fillBuffer(void* data, int size);
private:
	unsigned int id;
};