#pragma once

#include <memory>

#include "TypeDefs.h"
#include "../../opengl/shader/ShaderProgram.h"

struct Triangle {
	Triangle(
		const Point3D& p1,
		const Point3D& p2,
		const Point3D& p3,
		const Vector3D& scale,
		unsigned int textureId,
		std::shared_ptr<ShaderProgram> shader) : p1(p1), p2(p2), p3(p3), scale(scale), textureUnit(textureId), shader(shader) {}

	Point3D p1;
	Point3D p2;
	Point3D p3;
	Vector3D scale;
	unsigned int textureUnit;
	std::shared_ptr<ShaderProgram> shader;
	bool intersectible = true; // This should come from the constructor
};
