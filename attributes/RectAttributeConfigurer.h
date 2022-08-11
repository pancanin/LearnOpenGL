#pragma once

#include "AttributeConfigurer.h"

class RectAttributeConfigurer : public AttributeConfigurer {
public:
	std::vector<VertexAttribute> getAttributes() const;
};