#pragma once

#include "BufferSerialiser.h"

class RectBufferSerialiser : public BufferSerialiser {
public:
	float* serialise() const override;
	unsigned int size() const override;
};
