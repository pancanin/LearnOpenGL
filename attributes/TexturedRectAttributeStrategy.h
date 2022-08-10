#pragma once

#include "AttributeStrategy.h"

class TexturedRectAttributeStrategy : public AttributeStrategy {
public:
	std::vector<VertexAttribute> getAttributes() const;
};