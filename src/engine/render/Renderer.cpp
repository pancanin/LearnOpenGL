#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../models/TypeDefs.h"
#include "../models/Object.h"
#include "../models/Line.h"
#include "../models/Triangle.h"
#include "../models/Rect.h"
#include "../../opengl/shader/ShaderProgram.h"

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
	direction = glm::translate(direction, line.direction);
	direction = glm::scale(direction, glm::vec3(10.0f, 10.0f, 25.0f));
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
	rect.shader->use();

	std::shared_ptr<BufferSerialiser> bufferSerPtr = bufferSwitch.switchBuffer(ObjectType::RECT);

	auto model = glm::mat4(1.0f);

	model = glm::scale(model, rect.scale);
	rect.shader->setUniformMat4("model", model);
	rect.shader->setUniformMat4("projection", camera.getProjection());
	rect.shader->setUniformMat4("view", camera.getView());
	rect.shader->setInt("dtexture", rect.textureUnit);

	rect.shader->setUniformVec3("v1pos", rect.p1);
	rect.shader->setUniformVec3("v2pos", rect.p2);
	rect.shader->setUniformVec3("v3pos", rect.p3);
	rect.shader->setUniformVec3("v4pos", rect.p4);

	glDrawElements(GL_TRIANGLES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0);
}
