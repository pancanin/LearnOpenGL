#pragma once

#include "BufferSerialiser.h"

class TexturedRectBufferSerialiser : public BufferSerialiser {
public:
	float* serialise() const;
	unsigned int size() const;
};
