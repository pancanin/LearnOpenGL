#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../models/TypeDefs.h"
#include "../models/Object.h"
#include "../models/Line.h"
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

	auto startLineModel = glm::mat4(1.0f);
	startLineModel = glm::translate(startLineModel, line.start);
	lineShaderProgramPtr->setUniformMat4("lineStart", startLineModel);

	auto endLineModel = glm::mat4(1.0f);
	endLineModel = glm::translate(endLineModel, line.end);
	lineShaderProgramPtr->setUniformMat4("lineEnd", endLineModel);

	lineShaderProgramPtr->setUniformMat4("projection", camera.getProjection());
	lineShaderProgramPtr->setUniformMat4("view", camera.getView());

	lineShaderProgramPtr->setUniformVec4("color", line.color);

	bufferSwitch.switchBuffer(ObjectType::LINE);

	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
}
