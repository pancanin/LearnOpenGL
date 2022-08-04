#pragma once

#include "../models/Rect.h"
#include "ObjectComponent.h"

class RectComponent : public ObjectComponent<Rect>
{
public:
	void init(
		std::vector<VertexAttribute> attributes,
		unsigned int verticesPerObject,
		unsigned int componentsPerObject
	) override;

	void activate() override;

	void loadBuffer() override;

	void deactivate() override;
	
	void draw() override;
private:
	VertexBufferObject elementBuffer;
	static const unsigned int indicesCount = 6;
	unsigned int indices[indicesCount] = {
		0, 1, 3,
		1, 2, 3
	};
};

