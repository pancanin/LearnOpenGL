#include "RectComponent.h"

void RectComponent::init() {
	ObjectComponent<Rect>::init(Rect::getAttributes(), Rect::verticesPerRect, Rect::getComponentsCount());
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
}

void RectComponent::draw()
{
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

RectComponent::~RectComponent()
{
	deactivate();
}
