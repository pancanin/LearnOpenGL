#pragma once

#include "BufferSerialiser.h"
#include "../models/Rect.h"

class RectBufferSerialiser : public BufferSerialiser<Rect> {
public:
	float* serialise(const Rect& o) const override;
	unsigned int componentsCountPerObject() const override;
};
