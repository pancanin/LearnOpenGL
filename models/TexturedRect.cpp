#include "TexturedRect.h"

TexturedRect::TexturedRect(Point3D origin, float width, float height, unsigned int textureId) :
	Rect(origin, width, height), textureId(textureId) {}

