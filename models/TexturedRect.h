#pragma once

#include "Rect.h"

struct TexturedRect : public Rect {
	TexturedRect(unsigned int textureId, Point3D origin, float width, float height);

	unsigned int textureId;
};