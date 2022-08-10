#include "Rect.h"

#include "../utils/MathUtils.h"

Rect::Rect(Point3D origin, float width, float height) : origin(origin), width(width), height(height) {}

const unsigned int Rect::verticesPerRect = 4;