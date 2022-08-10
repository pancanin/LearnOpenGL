#pragma once

#include "SerialisationStrategy.h"
#include "../models/TexturedRect.h"

class TexturedRectSerialisationStrategy : public SerialisationStrategy<TexturedRect> {
public:
	float* serialise(const TexturedRect& o) const;
	unsigned int componentsCountPerObject() const;
};
