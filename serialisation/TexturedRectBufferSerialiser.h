#pragma once

#include "BufferSerialiser.h"
#include "../models/TexturedRect.h"

class TexturedRectBufferSerialiser : public BufferSerialiser<TexturedRect> {
public:
	float* serialise(const TexturedRect& o) const;
	unsigned int componentsCountPerObject() const;
};
