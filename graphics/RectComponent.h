#pragma once

#include <memory>

#include "../models/Rect.h"
#include "ObjectComponent.h"
#include "../attributes/AttributeStrategy.h"
#include "../serialisation/SerialisationStrategy.h"

template <typename RectType>
class RectComponent : public ObjectComponent<RectType>
{
public:
	void init(const AttributeStrategy& attributeStrategy, std::shared_ptr<SerialisationStrategy<RectType>> serialisationStragetyPtr) {
		ObjectComponent<RectType>::init(
			attributeStrategy.getAttributes(),
			RectType::verticesPerRect,
			serialisationStragetyPtr->componentsCountPerObject(),
			serialisationStragetyPtr);
		elementBuffer.init(GL_ELEMENT_ARRAY_BUFFER);
	}

	void activate() override {
		ObjectComponent<RectType>::activate();
		elementBuffer.bind();
	}

	void loadBuffer() override {
		ObjectComponent<RectType>::loadBuffer();
		elementBuffer.fillBuffer(indices, indicesCount);
	}

	void deactivate() override {
		ObjectComponent<RectType>::deactivate();
		elementBuffer.unbind();
	}
	
	void draw() override {
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	}

	~RectComponent() {
		deactivate();
	}
private:
	VertexBufferObject elementBuffer;
	static const unsigned int indicesCount = 6;
	unsigned int indices[indicesCount] = {
		1, 2, 3,
		0, 1, 3
	};
};

