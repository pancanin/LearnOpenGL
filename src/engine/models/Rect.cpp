#include "Rect.h"

Rect::Rect(
	const Point3D& p1,
	const Point3D& p2,
	const Point3D& p3,
	const Point3D& p4,
	const Vector3D& scale,
	unsigned int textureId,
	std::shared_ptr<ShaderProgram> shader,
	uint32_t textureScale
): 
	topLeft(p1), topRight(p2), bottomRight(p3), bottomLeft(p4), scale(scale),
	drawingData(DrawingData(textureId, shader, textureScale))
{}

const unsigned int Rect::verticesPerRect = 4;
