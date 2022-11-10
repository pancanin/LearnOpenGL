#pragma once
#include <memory>

#include "TypeDefs.h"
#include "../../opengl/shader/ShaderProgram.h"

struct Point {
	Point(const Point3D& position, const Color& color, float size, std::shared_ptr<ShaderProgram> shader) :
		position(position), color(color), size(size), shader(shader) {}

	Point3D position;
	Color color;
	float size;
	std::shared_ptr<ShaderProgram> shader;
};