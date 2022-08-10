#include "RectComponent.h"

void RectComponent::init(const AttributeStrategy& attributeStrategy, std::shared_ptr<SerialisationStrategy<Rect>> serialisationStragetyPtr) {
	ObjectComponent<Rect>::init(
		attributeStrategy.getAttributes(),
		Rect::verticesPerRect,
		serialisationStragetyPtr->componentsCountPerObject(),
		serialisationStragetyPtr);
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
