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
): Triangle(p1, p2, p3, scale, textureId, shader), p4(p4), textureScale(textureScale) {}

const unsigned int Rect::verticesPerRect = 4;
