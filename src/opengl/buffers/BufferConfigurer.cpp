#include "BufferConfigurer.h"

void BufferConfigurer::init(
	std::shared_ptr<BufferSerialiser> serialisation
) {
	this->serialisation = serialisation;
	this->vbo.init(GL_ARRAY_BUFFER);
	this->vao.init();
	this->ebo.init();

	activate();

	for (auto& attr : serialisation->attributes()) {
		this->vao.addAttribute(attr);
	}

	activate();
	loadBuffer();
}

void BufferConfigurer::activate() {
	this->vao.bind();
	this->vbo.bind();
	this->ebo.bind();
}

void BufferConfigurer::loadBuffer() {
	float* buffer = serialisation->serialise();
	vbo.fillBuffer(buffer, serialisation->size());
	delete[] buffer;

	unsigned int* indices = serialisation->indices();
	ebo.fillBuffer(indices, serialisation->indicesCount() * sizeof(unsigned int));
	delete[] indices;
}

void BufferConfigurer::deactivate() {
	this->vbo.unbind(); // TODO: Unbind rest of the buffer objects.
}

BufferConfigurer::~BufferConfigurer() {
	deactivate();
}