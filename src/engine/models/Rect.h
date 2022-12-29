#pragma once

#include <cstdint>

#include "TypeDefs.h"
#include "Triangle.h"

struct Rect : Triangle {
	Rect(
		const Point3D&,
		const Point3D&,
		const Point3D&,
		const Point3D&,
		const Vector3D& scale,
		unsigned int textureId,
		std::shared_ptr<ShaderProgram>,
		uint32_t textureScale
		);
	Rect() = default;

	Point3D p4;
	uint32_t textureScale;

	static const unsigned int verticesPerRect;
};
