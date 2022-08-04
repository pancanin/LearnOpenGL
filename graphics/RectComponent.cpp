#include "RectComponent.h"

void RectComponent::init(
	std::vector<VertexAttribute> attributes,
	unsigned int verticesPerObject,
	unsigned int componentsPerObject
) {
	ObjectComponent<Rect>::init(attributes, verticesPerObject, componentsPerObject);
	elementBuffer.init(GL_ELEMENT_ARRAY_BUFFER);
}

void RectComponent::activate() {
	ObjectComponent<Rect>::activate();
	elementBuffer.bind();
}

void RectComponent::loadBuffer() {
	ObjectComponent<Rect>::loadBuffer();
	elementBuffer.fillBuffer(indices, indicesCount);
}

void RectComponent::deactivate()
{
	ObjectComponent<Rect>::deactivate();
	elementBuffer.unbind();

	std::cout << "deactivate of rectcomponent called" << std::endl;
}

void RectComponent::draw()
{
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}
