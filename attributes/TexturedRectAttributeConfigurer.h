#pragma once

#include "AttributeConfigurer.h"

class TexturedRectAttributeConfigurer : public AttributeConfigurer {
public:
	std::vector<VertexAttribute> getAttributes() const;
};