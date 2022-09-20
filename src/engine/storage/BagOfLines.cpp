#include <iostream>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BagOfLines.h"
#include "../camera/Camera.h"
#include "../../opengl/models/LineVertex.h"

void BagOfLines::init(int bagSize)
{
	lines.reserve(bagSize);
	shader.init();
	shader.attachVertexShader("src/engine/shaders/line_vertex_shader");
	shader.attachFragmentShader("src/engine/shaders/line_fragment_shader");
	shader.link();
	shader.use();

	auto lineSerPtr = std::make_shared<LineBufferSerialiser>();

	std::vector<VertexAttribute> attributes = {
		VertexAttribute{ 0, sizeof(LineVertex::position) / sizeof(float), sizeof(LineVertex) / sizeof(float), 0 },
		VertexAttribute{ 1, sizeof(LineVertex::isEnd) / sizeof(float), sizeof(LineVertex) / sizeof(float), offsetof(LineVertex, LineVertex::isEnd) / sizeof(float) },
	};

	bufferConfig.init(attributes, lineSerPtr);
	bufferConfig.activate();
	bufferConfig.BufferConfigurer::loadBuffer();
}

Line& BagOfLines::add(const Line& o)
{
	lines.push_back(o);
	return lines[lines.size() - 1];
}

void BagOfLines::remove(const Line& l)
{
	for (auto it = lines.begin(); it != lines.end(); ++it) {
		if (&l == &*it) {
			lines.erase(it);
			break;
		}
	}
}

void BagOfLines::draw(const Camera& cam)
{
	shader.use();

	for (Line& line : lines) {
		auto startLineModel = glm::mat4(1.0f);
		startLineModel = glm::translate(startLineModel, line.start);
		shader.setUniformMat4("lineStart", startLineModel);

		auto endLineModel = glm::mat4(1.0f);
		endLineModel = glm::translate(endLineModel, line.end);
		shader.setUniformMat4("lineEnd", endLineModel);
		
		shader.setUniformMat4("projection", cam.getProjection());
		shader.setUniformMat4("view", cam.getView());

		shader.setUniformVec4("color", line.color);

		bufferConfig.activate();

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	}
}

std::vector<Line>::const_iterator BagOfLines::iter_begin() const
{
	return lines.cbegin();
}

std::vector<Line>::const_iterator BagOfLines::iter_end() const
{
	return lines.cend();
}
