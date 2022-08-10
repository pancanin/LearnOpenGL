#pragma once

#include "SerialisationStrategy.h"
#include "../models/Rect.h"

class RectSerialisationStrategy : public SerialisationStrategy<Rect> {
public:
	float* serialise(const Rect& o) const override;
	unsigned int componentsCountPerObject() const override;
};
