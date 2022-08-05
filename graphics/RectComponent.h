#pragma once

#include "../models/Rect.h"
#include "ObjectComponent.h"

class RectComponent : public ObjectComponent<Rect>
{
public:
	~RectComponent();

	void init();

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

