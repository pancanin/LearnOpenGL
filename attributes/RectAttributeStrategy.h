#pragma once

#include "AttributeStrategy.h"

class RectAttributeStrategy : public AttributeStrategy {
public:
	std::vector<VertexAttribute> getAttributes() const;
};