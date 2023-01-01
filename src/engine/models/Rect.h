#pragma once

#include <cstdint>

#include "TypeDefs.h"
#include "../../opengl/shader/ShaderProgram.h"
#include "DrawingData.h"

struct Rect {
	Rect(
		const Point3D& topLeft,
		const Point3D& topRight,
		const Point3D& bottomRight,
		const Point3D& bottomLeft,
		const Vector3D& scale,
		unsigned int textureId,
		std::shared_ptr<ShaderProgram>,
		uint32_t textureScale
		);
	Rect() = default;

	Point3D topLeft;
	Point3D topRight;
	Point3D bottomRight;
	Point3D bottomLeft;
	Point3D scale;
	DrawingData drawingData;

	static const unsigned int verticesPerRect;
};
