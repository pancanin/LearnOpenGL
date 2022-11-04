#pragma once

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
		std::shared_ptr<ShaderProgram>
		);
	Rect() = default;

	Point3D p4;

	static const unsigned int verticesPerRect;
};
