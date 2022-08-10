#pragma once

#include <memory>

#include "../models/Rect.h"
#include "ObjectComponent.h"
#include "../attributes/AttributeStrategy.h"
#include "../serialisation/SerialisationStrategy.h"

class RectComponent : public ObjectComponent<Rect>
{
public:
	~RectComponent();

	void init(const AttributeStrategy& attributeStrategy, std::shared_ptr<SerialisationStrategy<Rect>> serialisationStragetyPtr);

	void activate() override;

	void loadBuffer() override;

	void deactivate() override;
	
	void draw() override;
private:
	VertexBufferObject elementBuffer;
	static const unsigned int indicesCount = 6;
	unsigned int indices[indicesCount] = {
		1, 2, 3,
		0, 1, 3
	};
};

