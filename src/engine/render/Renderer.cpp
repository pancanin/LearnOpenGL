#include "Renderer.h"

#include <limits>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../models/TypeDefs.h"
#include "../models/Object.h"
#include "../models/Line.h"
#include "../models/Triangle.h"
#include "../models/Rect.h"
#include "../models/Point.h"
#include "../../opengl/shader/ShaderProgram.h"
#include "../Constants.h"

void Renderer::init()
{
	bufferSwitch.init();
}

void Renderer::render(const Camera& camera, const Object& obj)
{
	obj.shader->use();

	std::shared_ptr<BufferSerialiser> bufferSerPtr = bufferSwitch.switchBuffer(obj.type);
	auto model = glm::mat4(1.0f);

	model = glm::translate(model, obj.position);
	model = glm::rotate(model, glm::radians(obj.rotationAngle), obj.rotationAxis); // TODO: Explore rotation with quaternions. For now we will not rotate, but a rotation angle should be set in the object.
	model = glm::scale(model, obj.scaleFactor);

	obj.shader->setUniformMat4("model", model);
	obj.shader->setUniformMat4("projection", camera.getProjection());
	obj.shader->setUniformMat4("view", camera.getView());
	obj.shader->setInt("dtexture", obj.textureUnit);

	glDrawElements(GL_TRIANGLES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::render(const Camera& camera, const Line& line)
{
	if (lineShaderProgramPtr.get() == nullptr) {
		lineShaderProgramPtr = std::make_shared<ShaderProgram>();

		lineShaderProgramPtr->init();
		lineShaderProgramPtr->attachVertexShader("src/engine/shaders/line_vertex_shader");
		lineShaderProgramPtr->attachFragmentShader("src/engine/shaders/line_fragment_shader");
		lineShaderProgramPtr->link();
	}

	lineShaderProgramPtr->use();
	bufferSwitch.switchBuffer(ObjectType::LINE);

	auto startLineModel = glm::mat4(1.0f);
	startLineModel = glm::translate(startLineModel, line.start);
	lineShaderProgramPtr->setUniformMat4("lineStart", startLineModel);

	auto direction = glm::mat4(1.0f);
	float farPlane = 100.0f;
	direction = glm::translate(direction, line.direction * farPlane);
	lineShaderProgramPtr->setUniformMat4("direction", direction);

	lineShaderProgramPtr->setUniformMat4("projection", camera.getProjection());
	lineShaderProgramPtr->setUniformMat4("view", camera.getView());

	lineShaderProgramPtr->setUniformVec4("color", line.color);

	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
}

void Renderer::render(const Camera& camera, const Triangle& triangle)
{
	triangle.shader->use();

	std::shared_ptr<BufferSerialiser> bufferSerPtr = bufferSwitch.switchBuffer(ObjectType::TRIANGLE);

	auto model = glm::mat4(1.0f);

	model = glm::scale(model, triangle.scale);
	triangle.shader->setUniformMat4("model", model);
	triangle.shader->setUniformMat4("projection", camera.getProjection());
	triangle.shader->setUniformMat4("view", camera.getView());
	triangle.shader->setInt("dtexture", triangle.textureUnit);

	triangle.shader->setUniformVec3("triangle.v1", triangle.p1);
	triangle.shader->setUniformVec3("triangle.v2", triangle.p2);
	triangle.shader->setUniformVec3("triangle.v3", triangle.p3);

	glDrawElements(GL_TRIANGLES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::render(const Camera& camera, const Rect& rect)
{
	auto shader = rect.drawingData.shaderProgramPtr;
	shader->use();

	std::shared_ptr<BufferSerialiser> bufferSerPtr = bufferSwitch.switchBuffer(ObjectType::RECT);

	auto model = glm::mat4(1.0f);

	model = glm::scale(model, rect.scale);
	shader->setUniformMat4("model", model);
	shader->setUniformMat4("projection", camera.getProjection());
	shader->setUniformMat4("view", camera.getView());
	shader->setInt("dtexture", rect.drawingData.textureId);
	shader->setUniformF("textureScale", rect.drawingData.textureScale);

	shader->setUniformVec3(Constants::SHADER_VERTEX_1_POS, rect.topLeft);
	shader->setUniformVec3("v2pos", rect.topRight);
	shader->setUniformVec3("v3pos", rect.bottomRight);
	shader->setUniformVec3("v4pos", rect.bottomLeft);

	glDrawElements(GL_TRIANGLES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::render(const Camera& camera, const Point& point)
{
	point.shader->use();

	std::shared_ptr<BufferSerialiser> bufferSerPtr = bufferSwitch.switchBuffer(ObjectType::POINT);

	auto model = glm::mat4(1.0f);

	model = glm::translate(model, point.position);
	point.shader->setUniformMat4("model", model);
	point.shader->setUniformMat4("projection", camera.getProjection());
	point.shader->setUniformMat4("view", camera.getView());

	point.shader->setUniformVec4("color", point.color);
	point.shader->setUniformF("size", point.size);

	glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
}
