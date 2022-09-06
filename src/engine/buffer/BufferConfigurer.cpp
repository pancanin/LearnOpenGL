#include "BufferConfigurer.h"

void BufferConfigurer::init(
	std::vector<VertexAttribute> attributes,
	std::shared_ptr<BufferSerialiser> serialisation
) {
	this->serialisation = serialisation;
	this->vbo.init(GL_ARRAY_BUFFER);
	this->vao.init();

	activate();

	for (auto& attr : attributes) {
		this->vao.addAttribute(attr);
	}
}

void BufferConfigurer::activate() {
	this->vao.bind();
	this->vbo.bind();
}

void BufferConfigurer::loadBuffer() {
	float* buffer = serialisation->serialise();
	vbo.fillBuffer(buffer, serialisation->size());
	delete[] buffer;
}

void BufferConfigurer::deactivate() {
	this->vbo.unbind();
}

BufferConfigurer::~BufferConfigurer() {
	deactivate();
}