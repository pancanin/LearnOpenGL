#pragma once

#include "Rect.h"

struct TexturedRect : public Rect {
	TexturedRect(Point3D origin, float width, float height, unsigned int textureId);

	unsigned int textureId;
};