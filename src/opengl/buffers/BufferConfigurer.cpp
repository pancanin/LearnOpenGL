#include "BufferConfigurer.h"

BufferConfigurer& BufferConfigurer::init(
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

	loadBuffer();
}

BufferConfigurer& BufferConfigurer::activate() {
	this->vao.bind();
	this->vbo.bind();
	this->ebo.bind();
}

BufferConfigurer& BufferConfigurer::loadBuffer() {
	float* buffer = serialisation->serialise();
	vbo.fillBuffer(buffer, serialisation->size());
	delete[] buffer;

	unsigned int* indices = serialisation->indices();
	ebo.fillBuffer(indices, serialisation->indicesCount() * sizeof(unsigned int));
	delete[] indices;
}

BufferConfigurer& BufferConfigurer::deactivate() {
	this->vbo.unbind(); // TODO: Unbind rest of the buffer objects.
}

BufferConfigurer::~BufferConfigurer() {
	deactivate();
}